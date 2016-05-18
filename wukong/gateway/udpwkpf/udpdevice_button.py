from twisted.internet import reactor
from udpwkpf import WuClass, Device
import sys
from udpwkpf_io_interface import *

Button_Pin = 5

class Button(WuClass):
    def __init__(self):
        WuClass.__init__(self)
        self.loadClass('Button')
        self.IO = pin_mode(Button_Pin, PIN_TYPE_DIGITAL, PIN_MODE_INPUT)

    def update(self,obj,pID=None,val=None):
        try:
            current_value = digital_read(self.IO)
            print "Button value: %d" % current_value
            obj.setProperty(0, current_value)
        except IOError:
            print "Error"

if __name__ == "__main__":
    class MyDevice(Device):
        def __init__(self,addr,localaddr):
            Device.__init__(self,addr,localaddr)
            
        def init(self):
            m = Button()
            self.addClass(m,0)
            self.obj_button = self.addObject(m.ID)

    if len(sys.argv) <= 2:
        print 'python udpwkpf.py <ip> <port>'
        print '      <ip>: IP of the interface'
        print '      <port>: The unique port number in the interface'
        print ' ex. python udpwkpf.py 127.0.0.1 3000'
        sys.exit(-1)

    d = MyDevice(sys.argv[1],sys.argv[2])
    reactor.run()
    device_cleanup()