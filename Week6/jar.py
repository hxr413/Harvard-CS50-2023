class Jar:
    def __init__(self, capacity=12):
        if isinstance(self.capacity, int) == False or self.capacity < 0:
            raise ValueError

    def __str__(self):
        return self._size * '🍪'

    def deposit(self, n):
        self.size += n
        if self.size > self.capacity:
            raise ValueError

    def withdraw(self, n):
        if n > self.size:
            raise ValueError
        else:
            self.size -= n

    @property
    def capacity(self):
         return self.capacity
    # self._capacity?

    @property
    def size(self):
        return self.size
    # self._size?


def main():

    jar = Jar(10)

    jar.size = 8
    print(str(jar))

    jar.deposit(2)
    print(str(jar))

    jar.withdraw(1)
    print(str(jar))


main()
