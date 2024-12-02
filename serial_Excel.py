import serial
import time
from openpyxl import Workbook    
import keyboard
# Filepath
filepath = 'c:\\temp\\arduino\\\serial_Excel\\\serial_Excel.xlsx'
# Function to initialize and       return the serial connection
def init_serial():
    return serial.Serial('COM12', 9600, timeout=1) 
# Function to initialize and return an Excel workbook and wor ksheet
def init_excel():      
    wb = Workbook()    
    ws = wb.active
    ws.title = "Compass Readings"
    ws.append(["Timestamp", "x1", "y1", "z1", "x2", "y2", "z2", "x3", "y3", "z3"])
    return wb, ws
def main():
    ser = init_serial()
    wb, ws = init_excel() 
    last_timestamp = None
    try:
        while True:
            if ser.in_waiting:
                try:
                    data = ser.readline().decode('latin-1').strip()
                except UnicodeDecodeError:
                    # Handle decoding error
                    data = ser.readline().decode('latin-1', errors='replace').strip()
                if data:
                    print(f"Received: {data}")
                    # Split the received data into six values
                    values = data.split(',')
                    if len(values) == 9: 
                        x1_value, y1_value, z1_value, x2_value, y2_value, z2_value, x3_value, y3_value, z3_value = values
                        timestamp = time.strftime("%M:%S")
                        if timestamp != last_timestamp:
                            ws.append([timestamp, x1_value, y1_value, z1_value, x2_value, y2_value, z2_value, x3_value, y3_value, z3_value])
                            last_timestamp = timestamp
                    if len(values) == 6:
                        x1_value, y1_value, z1_value, x2_value, y2_value, z2_value = values
                        timestamp = time.strftime("%M:%S")
                        if timestamp != last_timestamp:
                            ws.append([timestamp, x1_value, y1_value, z1_value, x2_value, y2_value, z2_value])
                            last_timestamp = timestamp

            if keyboard.is_pressed('space'):
                print("Interrupted by spacebar")
                break
    except KeyboardInterrupt:
        print("Interrupted by user")
    finally:
        ser.close()
        wb.save(filepath)
        print(f"Excel file saved to {filepath}")
if __name__ == "__main__":
    main()  