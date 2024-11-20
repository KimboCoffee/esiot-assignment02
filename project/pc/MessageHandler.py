import serial

class MessageHandler:
    def __init__(self, port, baudrate):
        self.device = serial.Serial(port, baudrate=baudrate)

    def send(self, msg):
        self.device.write(msg)

    def read(self):
        return self.device.read()