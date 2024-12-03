
Serial_Excel_BNO085_magneto
Read Magnetometer data (calibrated, uncalibrated and RawMagnet0) from BNO085 and write to Excel file. 
Files are stored by default in  c:\temp\arduino\serial_Excel\ folder 

THe program serial_Excel.ino is running in Arduino, which is ocnnected via USB cable to computer.

![arduino-computer-connected](https://github.com/user-attachments/assets/3bdcb9c8-0bce-45cf-81fa-909b527736a1)

The upper  chart contains the "RawMAgnetometer) data. from the Reference manual: The magnetometer sensor reports raw readings from the physical magnetometer sensor. The
units are ADCs. Interpretation of the reported values is sensor dependent. The report ID is 0x16.

https://www.ceva-ip.com/wp-content/uploads/2019/10/SH-2-Reference-Manual.pdf

The lower chart contains  the calibrated magnetic field strength in nT (nano Teslo)


![image](https://github.com/user-attachments/assets/43f012bc-ff6d-4967-995b-b803effe1596)

The program serial_Excel.py is running in the computer, after hitting space in keyboard to stops to protocol the signals in COM port it generates a Excelfile.
Note: you have to adjust the COM port to what is in Arudino. 

![image](https://github.com/user-attachments/assets/b684cdf8-9a35-4d61-aeb4-f1d2fcb1e673)

The reason to write this program, was, that the calibrated magnetometer sometimes drifts, and the total field strength indicated is not what it should be according to what my geographical position. And  I am in the process to find out and reasearch if anything can be done about it.
