import glob
for filename in glob.glob('*.sol'):
  with open(filename) as f:
    first_line = f.readline()
    print(filename, first_line)
    f.close()