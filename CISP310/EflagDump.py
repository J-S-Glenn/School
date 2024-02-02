
flags = {
'CF_FLAG': (0x0001, "Carry Flag"), #Carry Flag
'OF_FLAG': (0x0800, "Overflow Flag"), #Overflow Flag
'SF_FLAG': (0x0080, 'Sign Flag'), #Sign Flag
'ZF_FLAG': (0x0040, "Zero Flag") #Zero Flag
}

while True:
    reg_val = int(input("What is the current EFL register value? "),16)

    for flag in flags.keys():
        if flags[flag][0] & reg_val == flags[flag][0]:
            print("{}\t SET  <------------".format(flags[flag][1]))
        else:
            print("{}\t NOT SET".format(flags[flag][1]))