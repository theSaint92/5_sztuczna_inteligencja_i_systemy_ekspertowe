import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np

dane = pd.read_csv('wine_results.csv',sep=';',encoding='cp1250',na_values=None)
pd.set_option('display.width', 400)
print(dane)

#KORELACJA
corr = dane.corr()
print(corr)
#Rysujemy
mask = np.zeros_like(corr)
mask[np.triu_indices_from(mask)] = True
sns.heatmap(corr, mask=mask) # sprawia że jest tylko po jednej stronie)
plt.xticks(rotation=40)
plt.yticks(rotation=40)
plt.tight_layout()
plt.title('Korelacja',y=0.98)
plt.show()