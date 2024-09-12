# Library
import I2C_LCD_driver
import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
from time import sleep
import base64
import requests

# Buzzer Pin
buzzer = 26

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(buzzer,GPIO.OUT)

# Inisialisasi LCD
lcd = I2C_LCD_driver.lcd()

# Inisialisasi RFID Reader
scan = SimpleMFRC522()

def send_to_api(encoded_id):
    url = "http://192.168.1.4:8000/api/rfid"
    data = {'encoded_id': encoded_id}
    response = requests.post(url, json=data)
    if response.status_code == 200:
        response_data = response.json()
        status = response_data.get('status', 'No status')
        keterangan = response_data.get('keterangan', 'No keterangan')
        print(status)
        print(keterangan)
    else:
        print(f"Failed to send data: {response.status_code} - {response.text}")
    
    lcd.lcd_clear()
    lcd.lcd_display_string(status, 1)
    lcd.lcd_display_string(keterangan, 2)

def encode_id(id):
    id_bytes = str(id).encode('utf-8')
    encoded_id = base64.b32encode(id_bytes).decode('utf-8')
    return encoded_id[:8]

lcd.lcd_display_string("Peminjaman Buku",1,0)
for a in range (0,15):
    lcd.lcd_display_string(".",2,a)
    sleep(0.3)

while True:
    lcd.lcd_clear()

    print("Tempelkan RFID")      
    lcd.lcd_display_string("Tempelkan RFID",1,1)

    id,Tag = scan.read()                    
    print("Original Tag ID : " + str(id))
    encoded_id = encode_id(id)
    print("Encoded Tag ID : " + encoded_id)
    print("--------------------------------")
    lcd.lcd_clear()
    lcd.lcd_display_string("Tag ID",1,5)
    lcd.lcd_display_string(encoded_id,2,4)

    GPIO.output(buzzer,GPIO.HIGH)
    sleep(0.5)
    GPIO.output(buzzer,GPIO.LOW)
    
    sleep(1)
    send_to_api(encoded_id)
    
    sleep(2)

GPIO.cleanup()
