import serial

class MessageHandler:
    def __init__(self):
        self.baudrate = 9600
        self.port = "COM4"
        self.device = serial.Serial(port, baudrate)

    def send(self, msg):
        self.device.write(msg)

    def read(self):
        return self.device.read()