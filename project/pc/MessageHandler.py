import serial

class MessageHandler:
    def __init__(self):
        self.baudrate = 9600
        self.port = "COM4"
        self.device = serial.Serial(self.port, self.baudrate)

    def send(self, msg):
        self.device.write(msg)

    def read(self):
        return self.device.read()