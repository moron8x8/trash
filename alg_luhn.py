def alg_luhn(s):
   reversed_s = str(s)[::-1]
   summa = 0
   for i in range(len(reversed_s)):
      if i % 2 == 1:
         c_num = int(reversed_s[i]) * 2
         if c_num >= 10:
            c_num = sum(int(i) for i in str(c_num))
      else: c_num = int(reversed_s[i])
      summa += c_num

   return summa % 10 == 0

number_of_card = input().strip()
print(alg_luhn(number_of_card))