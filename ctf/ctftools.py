#!/usr/bin/env python
import socket

class Conn:
    def __init__(self, ip, port):
        conn = socket.socket()
        conn.connect((ip, port))
        self.conn = conn

    def recv(self, n):
        return self.conn.recv(n)

    def recvuntil(self, s):
        length = len(s)
        c = ''
        while True:
            c += self.conn.recv(1)
            if s in c:
                print '[!] Recieved...'
                print c
                return c

    def sendline(self, s):
        print '[!] Sent..'
        print s
        self.conn.send(s + '\n')

def remote(ip, port):
    return Conn(ip, port)

def quick_mulmod(a, b, c):
    ans = 0
    a = a % c
    while b != 0:
        if b & 1 :
            ans = (ans + a) % c
        a = (2*a) % c
        b >>= 1
    return ans

def quick_powmod(a, b, c):
    a = a % c
    ans = 1 # 存放结果
    while b != 0:
        if b & 1: # 二进制与
            ans = (ans * a) % c
        a = (a * a) % c # 取模是防止溢出
        b >>= 1 # 二进制向右移动一位
    return ans

