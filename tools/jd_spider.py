#!/usr/bin/env python3
from lxml import etree
from selenium import webdriver
from time import sleep
import random
from fake_useragent import UserAgent

def JD_Spider(url):
    chrome_driver="/usr/local/bin/chromedriver"
    options=webdriver.ChromeOptions()
    options.add_argument("--headless")
    options.add_argument("user-agent="+UserAgent().random)
    chrome=webdriver.Chrome(chrome_options=options,executable_path=chrome_driver)
    for i in range(100):
        print("====Crawling Page "+str(i))
        chrome.get(url.format(str(2*i+1),str(50*i+2)))
        js="var p=document.documentElement.scrollTop=100000"
        chrome.execute_script(js)
        sleep(3+random.random())
        html=chrome.page_source
        tree=etree.HTML(html)
        names=tree.xpath('//div[@id="J_goodsList"]/ul/li/div/div[3]/a/em')
        prices=tree.xpath('//*[@id="J_goodsList"]/ul/li/div/div[2]/strong/i/text()')
        hrefs=tree.xpath('//*[@id="J_goodsList"]/ul/li/div/div[1]/a/@href')
        for name,price,href in zip(names,prices,hrefs):
            #with open("data/JD_mac_pro_goods_list.txt","a",encoding="utf-8") as f:
            #    f.write("商品:"+name.xpath('string(.)')+" 价格: "+price+" 链接: "+"https:"+href+"\n")
            print("商品:"+name.xpath('string(.)')+" 价格: "+price+" 链接: "+"https:"+href+"\n")
        print("====Finishing Page "+str(i))

if __name__=='__main__':
    url="https://search.jd.com/Search?keyword=mac%20pro&enc=utf-8&qrst=1&rt=1&stop=1&vt=2&bs=1&wq=mac%20pro&ev=exbrand_Apple%5E&page={}&s={}&click=0"
    #url="https://search.jd.com/Search?keyword=mac%20pro&enc=utf-8&qrst=1&rt=1&stop=1&vt=2&bs=1&wq=mac%20pro&ev=exbrand_Apple%5E&page=5&s=102&click=0"
    #url="https://search.jd.com/Search?keyword=mac%20pro&enc=utf-8&qrst=1&rt=1&stop=1&vt=2&bs=1&wq=mac%20pro&ev=exbrand_Apple%5E&page=7&s=152&click=0"
    JD_Spider(url)
