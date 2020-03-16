clear all; %#ok<CLALL>
clc;
close all;

% load ../testCase/Mesh/VX.txt
% load ../testCase/Mesh/VY.txt
% load ../testCase/Mesh/VZ.txt

load ../meshGenerator/VX.txt
load ../meshGenerator/VY.txt
load ../meshGenerator/VZ.txt

load ../testCase/Mesh/CX.txt
load ../testCase/Mesh/CY.txt
load ../testCase/Mesh/CZ.txt

load ../testCase/Mesh/CfX.txt
load ../testCase/Mesh/CfY.txt
load ../testCase/Mesh/CfZ.txt


load ../testCase/Mesh/SfX.txt
load ../testCase/Mesh/SfY.txt
load ../testCase/Mesh/SfZ.txt


load ../testCase/Mesh/magSf.txt

load ../testCase/Mesh/V.txt

load ../testCase/Mesh/fx.txt

load ../testCase/Mesh/dX.txt
load ../testCase/Mesh/dY.txt
load ../testCase/Mesh/dZ.txt

load ../testCase/Mesh/magd.txt

load ../testCase/Mesh/patchID.txt

figure(1)
surface(VX,VY,VZ)
axis tight equal
grid on;
grid minor;
box on;
ax = gca;
ax.XRuler.Axle.LineWidth = 2;
ax.YRuler.Axle.LineWidth = 2;
% ax.XColor = 'blue';
% ax.YColor = 'blue';
xlabel('X-Position', 'FontSize', 20);
ylabel('Y-Position', 'FontSize', 20);
title({'Grid Generation - Cell Vertices'}, 'FontSize', 15);
xAX = get(gca,'XAxis');
set(xAX,'FontSize', 15)
yAX = get(gca,'YAxis');
set(yAX,'FontSize', 15)
saveas(gcf,'figure1.png')


% figure(2)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CX(:),CY(:),35,CY(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-CellCenters'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure2.png')



% figure(3)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% 
% hold on
% scatter(CfX(:),CfY(:),35,CfY(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-FaceCenters'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure3.png')



% figure(4)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% 
% hold on
% scatter(CfX(:),CfY(:),35,SfX(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% axis tight equal
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-FaceAreasX'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure4.png')

% figure(5)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% 
% hold on
% scatter(CfX(:),CfY(:),35,SfY(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% axis tight equal
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-FaceAreasY'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure5.png')


% figure(6)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% 
% hold on
% scatter(CfX(:),CfY(:),35,SfZ(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% axis tight equal
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-FaceAreasZ'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure6.png')



% figure(7)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CfX(:),CfY(:),35,magSf(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-FaceAreasMagnitude'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure7.png')

% figure(8)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% hold on
% scatter(CX(:),CY(:),35,V(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% 
% 
% title({'Grid Generation- Cell Volumes'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure8.png')

% figure(9)
% surface(VX,VY,0*VX)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CfX(:),CfY(:),35,fx(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-InterpolationFactor'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure9.png')

% figure(10)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CfX(:),CfY(:),35,dX(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-CellToCellDistanceX'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure10.png')

% 
% figure(11)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CfX(:),CfY(:),35,dY(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-CellToCellDistanceY'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure11.png')



% figure(12)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CfX(:),CfY(:),35,dZ(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-CellToCellDistanceZ'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure12.png')




% figure(13)
% surface(VX,VY,VZ)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% hold on
% scatter(CfX(:),CfY(:),35,magd(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-celltocelldistanceMagnitude'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure13.png')


% 
% figure(14)
% surface(VX,VY,0*VX)
% axis tight equal
% ax = gca;
% ax.XRuler.Axle.LineWidth = 2;
% ax.YRuler.Axle.LineWidth = 2;
% grid on;
% grid minor;
% box on;
% % ax.XColor = 'blue';
% % ax.YColor = 'blue';
% 
% 
% hold on
% scatter(CfX(:),CfY(:),35,patchID(:),'filled','MarkerEdgeColor','black', 'LineWidth',1.5)
% col = colorbar;
% col.FontSize = 20;
% xlabel('X-Position', 'FontSize', 20);
% ylabel('Y-Position', 'FontSize', 20);
% title({'Grid Generation-BoundaryID'}, 'FontSize', 15);
% xAX = get(gca,'XAxis');
% set(xAX,'FontSize', 15)
% yAX = get(gca,'YAxis');
% set(yAX,'FontSize', 15)
% saveas(gcf,'figure14.png')
% 
