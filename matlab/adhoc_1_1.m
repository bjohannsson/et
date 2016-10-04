

distance = [1 15 47 87 60 100 120 150 180 250 1 15 30 50 70 100 150];
distance = distance/100;
n = length(distance);
rssi = [-40 -39 -40 -40 -41;
    -47 -49 -48 -49 -50;
    -46 -45 -45 -45 -44;
    -62 -61 -61 -59 -62;
    -46 -44 -44 -46 -43;
    -50 -50 -50 -50 -51;
    -56 -55 -55 -52 -54
    -52 -53 -53 -51 -52
    -53 -54 -54 -55 -55
    -58 -59 -59 -60 -59
    -36 -36 -35 -36 -40
    -40 -40 -39 -39 -39
    -44 -44 -44 -44 -44
    -50 -52 -52 -52 -51
    -51 -50 -50 -50 -50
    -52 -52 -53 -51 -52
    -55 -54 -54 -54 -53];

rssi_mean = zeros(1, n);

for i = 1:n
    rssi_mean(i) = mean(rssi(i,:));

end
for i = 1:n
    for j = 1:5
        plot(distance(i), rssi(i,j), 'bx'), hold on
    end
    plot(distance(i), rssi_mean(i), 'ro', 'linewidth', 3)
end


% plot(distance(1), rssi(1,2), 'o')
