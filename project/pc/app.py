import MessageHandler
import View
import time

gui = View.GUI()
msgHandler = MessageHandler.MessageHandler()
gui.mainMenu(0,0)

while True:
    msg = msgHandler.read()
    if msg != None:
        gui.update(msg.getTemp(), msg.getLevel())
        time.sleep(float(msg.getPeriod()) / 1000)