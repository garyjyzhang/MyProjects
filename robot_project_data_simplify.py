def simplify_data(Data2):
	Data = []
	for i in range(len(Data2)):
		print Data2[i];
		Data.append(float(Data2[i]))

	L = len(Data) / 12
	price = []
	xx = [0, Data[0]]
	price.append(xx)
	for i in range(12):
		start = i * L;
		endd = i * L + L;
		for j in range(start, endd + 1):
			Min = start
			for k in range(j, endd):
				if (Data[k] < Data[Min]): Min = k;
			temp = Data[j]; 
			Data[j] = Data[Min]; 
			Data[Min] = temp;
		avg = 0
		for j in range(start + 5, endd - 4):
			avg = avg + Data[j];
		avg /= (L - 10)
		xx = [i * 2 + 1, avg]
		price.append(xx)
	xx = [24, Data[len(Data) - 1]]
	price.append(xx)
	return price