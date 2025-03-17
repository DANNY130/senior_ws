import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/olympusolutions/senior_ws/src/riley_ws/install/my_package'
