import MessageHandler
import View
import time

gui = View.GUI()
msgHandler = MessageHandler.MessageHandler()
gui.mainMenu(0,0)

msgHandler.clearBuf()

while True:
    msg = msgHandler.read()
    gui.update(msg.getTemp(), msg.getLevel())
    if gui.wasTempReset() == 1 :
        print("Temperature was reset")
    if gui.wasContainerEmptied() == 1:
        print("Container was emptied")
    time.sleep(float(msg.getPeriod()) / 1000)