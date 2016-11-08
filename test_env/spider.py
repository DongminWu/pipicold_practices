import requests


if __name__ == '__main__':
    ret = requests.get("www.baidu.com")
    print ret.text
