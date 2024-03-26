import matplotlib.pyplot as plt
from collections import Counter

# 讀取文本檔
filename = 'random_data.txt'
with open(filename, 'r') as file:
    text = file.read()

# 使用 Counter 來統計每個字元出現的次數
character_count = Counter(text)

# 提取字元和對應的出現次數
chars = []
counts = []
for char, count in sorted(character_count.items()):
    chars.append(char)
    counts.append(count)

# 繪製長條圖
plt.figure(figsize=(10, 6))
plt.bar(chars, counts)
plt.xlabel('char')
plt.ylabel('frequency of occurrences')
plt.title('Character Frequency')
#plt.xticks(rotation=90)
plt.show()
