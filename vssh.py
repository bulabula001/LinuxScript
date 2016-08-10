
import pexpect
import sys


#ip="192.168.31.130"


import pexpect
import sys


#ip="192.168.31.130"

user="root"

passwd="toor"

for i in range(1,len(sys.argv)):

        child=pexpect.spawn('/usr/bin/ssh',[user+'@'+sys.argv[i]])

        try:
                child.expect('(?i)password')
                child.sendline(passwd)
                child.expect('#')
                child.sendline()
                child.expect('#')
                print child.before
                child.sendline('pwd | wc -l > auto.log')
                child.sendline('dir >> auto.log')
                child.sendline('who am i >>auto.log')
                child.sendline('exit')

        except EOF:
                print "except EOF"
        except TIMEOUT:
                print "except TIMEOUT"
