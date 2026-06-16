import random

def main():
    exchange_num = int(input("number of exchanges: "))
    people_num = int(input("number of people: "))
    initial_cap = int(input("initial capital: "))

    arr = [initial_cap] * people_num
    for i in range(exchange_num):
        exchange(arr)
    
    arr.sort(reverse=True)

    for i in arr:
        print(f"{i:.2f}")

def exchange(arr):
    i, j = random_pair(len(arr))
    amount = min(arr[i], arr[j]) * 0.1
    if coin_flip():
        arr[i] += amount
        arr[j] -= amount
    else:
        arr[j] += amount
        arr[i] -= amount 

def random_pair(max):
    a = random.randrange(0, max)
    b = random.randrange(0, max)
    return a, b

def coin_flip():
    return random.randint(0, 1) == 1

if __name__ == '__main__':
    main()