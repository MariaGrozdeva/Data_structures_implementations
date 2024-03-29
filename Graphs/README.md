Реализираният граф е **тегловен ориентиран мултиграф**.  
(Изключение прави реализацията чрез **матрица на съседство**. Там графът е:  
1. тегловен (като не можем да имаме ребро с тегло 0, защото става двусмислица)
2. ориентиран
3. обикновен граф  

В останалите реализации можем да постигнем **нетегловен неориентиран граф/мултиграф** като:  
* Всички ребра в тегловния граф правим с тегло 1.  
* За всяко извикване на функцията addEdge добавяме две ребра - по едно за всяка посока.  

**Списък на наследници. (Adjacency list)**  
![alt text](https://i.ibb.co/yPPp6Ds/adj-List-Graph.jpg)  

**Матрица на съседство. (Adjacency matrix)**  
![alt text](https://i.ibb.co/yqJbWLW/adj-Matrix-Graph.jpg)  

**Списък на ребра. (Edges list)**  
![alt text](https://i.ibb.co/yVS2sBM/edge-List-Graph.jpg)  
