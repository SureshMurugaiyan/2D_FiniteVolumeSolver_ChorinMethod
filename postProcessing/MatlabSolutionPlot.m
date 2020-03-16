clear all; %#ok<CLALL>
clc;
% close all;

load ../testCase/Mesh/CX.txt
load ../testCase/Mesh/CY.txt


load ../testCase/0/mu.txt
load ../testCase/0/rho.txt
load ../testCase/0/UX.txt
load ../testCase/0/UY.txt
load ../testCase/0/UZ.txt
load ../testCase/0/p.txt
load ../testCase/0/divphiU.txt

% 
% load ../testCase/1/mu.txt
% load ../testCase/1/rho.txt
% load ../testCase/1/UX.txt
% load ../testCase/1/UY.txt
% load ../testCase/1/UZ.txt
% load ../testCase/1/p.txt
% load ../testCase/1/divphiU.txt


% load ../testCase/10/mu.txt
% load ../testCase/10/rho.txt
% load ../testCase/10/UX.txt
% load ../testCase/10/UY.txt
% load ../testCase/10/UZ.txt
% load ../testCase/10/p.txt
% load ../testCase/10/divphiU.txt

% load ../testCase/30/mu.txt
% load ../testCase/30/rho.txt
% load ../testCase/30/UX.txt
% load ../testCase/30/UY.txt
% load ../testCase/30/UZ.txt
% load ../testCase/30/p.txt
% load ../testCase/30/divphiU.txt
% % 
% 
% load ../testCase/50/mu.txt
% load ../testCase/50/rho.txt
% load ../testCase/50/UX.txt
% load ../testCase/50/UY.txt
% load ../testCase/50/UZ.txt
% load ../testCase/50/p.txt
% load ../testCase/50/divphiU.txt



% load ../testCase/100/mu.txt
% load ../testCase/100/rho.txt
% load ../testCase/100/UX.txt
% load ../testCase/100/UY.txt
% load ../testCase/100/UZ.txt
% load ../testCase/100/p.txt
% load ../testCase/100/divphiU.txt


% load ../testCase/200/mu.txt
% load ../testCase/200/rho.txt
% load ../testCase/200/UX.txt
% load ../testCase/200/UY.txt
% load ../testCase/200/UZ.txt
% load ../testCase/200/p.txt
% load ../testCase/200/divphiU.txt

% load ../testCase/500/mu.txt
% load ../testCase/500/rho.txt
% load ../testCase/500/UX.txt
% load ../testCase/500/UY.txt
% load ../testCase/500/UZ.txt
% load ../testCase/500/p.txt
% load ../testCase/500/divphiU.txt


load ../testCase/1000/mu.txt
load ../testCase/1000/rho.txt
load ../testCase/1000/UX.txt
load ../testCase/1000/UY.txt
load ../testCase/1000/UZ.txt
load ../testCase/1000/p.txt
load ../testCase/1000/divphiU.txt

% load ../testCase/2000/mu.txt
% load ../testCase/2000/rho.txt
% load ../testCase/2000/UX.txt
% load ../testCase/2000/UY.txt
% load ../testCase/2000/UZ.txt
% load ../testCase/2000/p.txt
% load ../testCase/2000/divphiU.txt
% % 
% 
% load ../testCase/5000/mu.txt
% load ../testCase/5000/rho.txt
% load ../testCase/5000/UX.txt
% load ../testCase/5000/UY.txt
% load ../testCase/5000/UZ.txt
% load ../testCase/5000/p.txt
% load ../testCase/5000/divphiU.txt
% 

load ../testCase/10000/mu.txt
load ../testCase/10000/rho.txt
load ../testCase/10000/UX.txt
load ../testCase/10000/UY.txt
load ../testCase/10000/UZ.txt
load ../testCase/10000/p.txt
load ../testCase/10000/divphiU.txt

% 
% load ../testCase/20000/mu.txt
% load ../testCase/20000/rho.txt
% load ../testCase/20000/UX.txt
% load ../testCase/20000/UY.txt
% load ../testCase/20000/UZ.txt
% load ../testCase/20000/p.txt
% load ../testCase/20000/divphiU.txt


load ../testCase/30000/mu.txt
load ../testCase/30000/rho.txt
load ../testCase/30000/UX.txt
load ../testCase/30000/UY.txt
load ../testCase/30000/UZ.txt
load ../testCase/30000/p.txt
load ../testCase/30000/divphiU.txt


% 
% load ../testCase/35000/mu.txt
% load ../testCase/35000/rho.txt
% load ../testCase/35000/UX.txt
% load ../testCase/35000/UY.txt
% load ../testCase/35000/UZ.txt
% load ../testCase/35000/p.txt
% load ../testCase/35000/divphiU.txt
% 
% load ../testCase/40000/mu.txt
% load ../testCase/40000/rho.txt
% load ../testCase/40000/UX.txt
% load ../testCase/40000/UY.txt
% load ../testCase/40000/UZ.txt
% load ../testCase/40000/p.txt
% load ../testCase/40000/divphiU.txt

% load ../testCase/49000/mu.txt
% load ../testCase/49000/rho.txt
% load ../testCase/49000/UX.txt
% load ../testCase/49000/UY.txt
% load ../testCase/49000/UZ.txt
% load ../testCase/49000/p.txt
% load ../testCase/49000/divphiU.txt

load ../testCase/50000/mu.txt
load ../testCase/50000/rho.txt
load ../testCase/50000/UX.txt
load ../testCase/50000/UY.txt
load ../testCase/50000/UZ.txt
load ../testCase/50000/p.txt
load ../testCase/50000/divphiU.txt

load ../testCase/100000/mu.txt
load ../testCase/100000/rho.txt
load ../testCase/100000/UX.txt
load ../testCase/100000/UY.txt
load ../testCase/100000/UZ.txt
load ../testCase/100000/p.txt
load ../testCase/100000/divphiU.txt

% 
% load ../testCase/180000/mu.txt
% load ../testCase/180000/rho.txt
% load ../testCase/180000/UX.txt
% load ../testCase/180000/UY.txt
% load ../testCase/180000/UZ.txt
% load ../testCase/180000/p.txt
% load ../testCase/180000/divphiU.txt
% 
% 
% load ../testCase/200000/mu.txt
% load ../testCase/200000/rho.txt
% load ../testCase/200000/UX.txt
% load ../testCase/200000/UY.txt
% load ../testCase/200000/UZ.txt
% load ../testCase/200000/p.txt
% load ../testCase/200000/divphiU.txt


load ../testCase/250000/mu.txt
load ../testCase/250000/rho.txt
load ../testCase/250000/UX.txt
load ../testCase/250000/UY.txt
load ../testCase/250000/UZ.txt
load ../testCase/250000/p.txt
load ../testCase/250000/divphiU.txt


load ../testCase/500000/mu.txt
load ../testCase/500000/rho.txt
load ../testCase/500000/UX.txt
load ../testCase/500000/UY.txt
load ../testCase/500000/UZ.txt
load ../testCase/500000/p.txt
load ../testCase/500000/divphiU.txt


figure(1)
[~,h] =contourf(CX,CY,UX,60);
axis tight equal
% grid on;
% grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;

hcb=colorbar;
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_x-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure1.png')


figure(2)
[~,h] =contourf(CX,CY,UY,60);
axis tight equal
% grid on;
% grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;

hcb=colorbar;
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_y-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure2.png')


figure(3)
[~,h] =contourf(CX,CY,UZ,60);
axis tight equal
% grid on;
% grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;

colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_z-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure3.png')

figure(4)
[~,h] =contourf(CX,CY,p,60);
axis tight equal
% grid on;
% grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;

colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$Pressure$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure4.png')

% 
figure(5)
[~,h] =contourf(CX,CY,divphiU,60);
axis tight equal
% grid on;
% grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;

colorbar
set(h,'LineColor','none')
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$Divergence$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure5.png')

figure(6)
surf(CX,CY,UX);
axis tight equal
% grid on;
% grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;

hcb=colorbar;
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'$U_x-Velocity$'}, 'FontSize', 15,'Interpreter','latex');
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'Sol_figure6.png')
