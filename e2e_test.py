import subprocess


def run_test():
	proc = subprocess.Popen(['bin/median_calc'], shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
	proc.stdin.write(b'5 1 7 m m 8 8 m\n')
	proc.stdin.flush()
	expected = b"5 5 7 "
	out = proc.stdout.read(len(expected))
	if expected != out:
		print("Expected: {}, provided: {}".format(expected, out))
	proc.stdin.write(b'm 9 m\n')
	proc.stdin.flush()
	expected = b"7 7.5 "
	out = proc.stdout.read(len(expected))
	if expected != out:
		print("Expected: {}, provided: {}".format(expected, out))	
	proc.stdin.write(b'q\n')
	proc.stdin.flush()

if __name__ == "__main__":
	run_test()
	print("Test completed")