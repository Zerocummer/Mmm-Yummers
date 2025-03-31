import serial  # настройка COM порта
import time

port = 'COM5'
boudrate = 9600
ser = serial.Serial(port, boudrate, timeout=1)
time.sleep(2)
with open('arduino.txt', 'a+') as file:
    file.write('1')
    k = 0
    try:
        while k <= 5:
            if ser.in_waiting:
                data = ser.readline().decode('utf-8').strip()
                print(data)
                file.write(data + '\n')
                k += 1
    except KeyboardInterrupt:
        print('No')
ser.close()
