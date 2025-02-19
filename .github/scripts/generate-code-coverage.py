#!/usr/bin/python3

import os
import subprocess

home_dir = os.getcwd()

os.chdir('tests')
subprocess.run(['ctest', '-C', 'Debug', '--verbose'])

os.chdir(home_dir)
subprocess.run(['lcov', '-c', '-d', '.', '--remove', 'libreoffice_total.info', 'tests/*', '-o', 'code-coverage.info', '--include', '*.cpp', '--include', '*.hpp', '--ignore-errors', 'mismatch'])
subprocess.run(['genhtml', 'code-coverage.info', '--output-directory', 'code_coverage'])
