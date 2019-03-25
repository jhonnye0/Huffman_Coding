x = linspace(0,10,100); % (consertar essa descrição) limits of the axis-x and 100 is the number of points of the graph
filename = 'inputlist.txt';
delimiterIn = ' '; %declare the character used to separate de columnsin the input
headerlinesIn = 1; %declare the number of lines of the header of the .txt
A = importdata(filename,delimiterIn,headerlinesIn);
x = A.data(:, 1);
y = A.data(:, 2);
plot(x,y)
hold on %plot other graph in the same plane
filename = 'inputabb.txt';
delimiterIn = ' '; %declare the character used to separate de columnsin the input
headerlinesIn = 1; %declare the number of lines of the header of the .txt
B = importdata(filename,delimiterIn,headerlinesIn);
y2 = B.data(:, 2);
plot(x,y2)
hold off
xlabel('number of nodes')
ylabel('number of comparisons')
title('Lists vs ABB - Comparison')