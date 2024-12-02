
Serial_Excel_BNO085_magneto
Read Magnetometer data (calibrated, uncalibrated and RawMagnet0) from BNO085 and write to Excel file. 
Files are stored by default in  c:\temp\arduino\serial_Excel\ folder 

THe program serial_Excel.ino is running in Arduino, which is ocnnected via USB cable to computer.

![arduino-computer-connected](https://github.com/user-attachments/assets/80b032db-1dd5-4b8e-a723-2fdc6002f18e)


The program serial_Excel.py is running in the computer, after hitting space in keyboard to stops to protocol the signals in COM port it generates a Excelfile.
Note: you have to adjust the COM port to what is in Arudino. 

![image](https://github.com/user-attachments/assets/b684cdf8-9a35-4d61-aeb4-f1d2fcb1e673)

The reason to write this program, was, that the calibrated magnetometer sometimes drifts, and the total field strength indicated is not what it should be according to what my geographical position. And  I am in the process to find out and reasearch if anything can be done about it.
