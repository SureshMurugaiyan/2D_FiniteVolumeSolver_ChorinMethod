clear all; %#ok<CLALL>
clc;
close all;

load VX.txt
load VY.txt
load VZ.txt

R  = sqrt(VX.^2 + VY.^2);
theta =  atan(VY./VX);
VR = (1-1./(R.^2))*cos(theta);
Vtheta = -(1+1./(R.^2))*sin(theta);
velX = VR.*cos(theta)-Vtheta.*sin(theta);
velY = VR.*sin(theta)+Vtheta.*cos(theta);

Vel = sqrt(velX.^2 + velY.^2);

figure(1)
surface(VX,VY,VZ);
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'Grid Generation'}, 'FontSize', 15);
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
axis image
saveas(gcf,'figure1.png')

