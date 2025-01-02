// https://leetcode.com/discuss/interview-question/1647092/coinbase-virtual-on-site-interview-questions

/*
You are given a list of currency relationships with exchange values. Find the best exchange rate from currency1 to currency2.
There is no possiblility of arbitrage.

Test 1: 
USD,CAD,1.3;USD,GBP,0.71;USD,JPY,109;GBP,JPY,155
USD
JPY

Output: 110.05

Test 2: 
USD,GBP,0.7;USD,JPY,109;GBP,JPY,155;CAD,CNY,5.27;CAD,KRW,921
USD
CNY

Output: -1.0
*/



/*
It's a really hard problem in my opinion for a 45-min interview! 
First you need to create a graph with the exchange rate as the edge weight. 
Whatever path that gives you the higher value when multiplying the edges is your solution. 
First you need to convert the problem to a shortest path problem. 

To do so:
Instead of finding the value of E1 x E2 x E3 ... and find the path with max value, find the max value for
log(E1 x E2 x E3 ...) = log(E1) + log(E2) + log(E3) + ...

For the shortest path, we look for the minimum value, so we multiply each edge by -1. 
Now we are looking for a min value for:
-log(E1 x E2 x E3 ...) = -log(E1) - log(E2) - log(E3) - ....

Thus after taking a logarithm of edges weight and negating them, we have a shortest path problem with negative edges. 
Dijkstra doesn't work so we need to apply Bellman-Ford algorithm.
*/
