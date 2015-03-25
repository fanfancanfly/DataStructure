%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%局外点符合模型的有多少,通过点到线的距离来判断%%%%%%%%%%%%%%%%%%%%%%%%%
%Consensus_Setx     原来的x局内点
%Consensus_Sety     原来的y局内点
%Maybe_outliersx    x局外点
%Maybe_outliersy    y局外点
%line_vec           直线的系数
%point_line_dis     点到直线的距离阈值
function [Re_Consensus_Set2d,Re_Consensus_Set3d] = AgreeWithModel(Consensus_Setx,Consensus_Sety,Maybe_outliersx,Maybe_outliersy,line_vec,point_line_dis)
Consensus_Set_temx = Consensus_Setx;                %临时变量进行保存
Consensus_Set_temy = Consensus_Sety;
[m,n] = size(Maybe_outliersx);
for i=1:m
    distem = abs(line_vec(1,1)*Maybe_outliersx(i,1)+line_vec(1,2)-Maybe_outliersy(i,1))/sqrt(line_vec(1,1)^2+1);           %判断点到直线的距离
    if (distem < point_line_dis)
        Consensus_Set_temx = [Consensus_Set_temx;Maybe_outliersx(i,1)];
        Consensus_Set_temy = [Consensus_Set_temy;Maybe_outliersy(i,1)];
    end
end
Re_Consensus_Set2d = Consensus_Set_temx;
Re_Consensus_Set3d = Consensus_Set_temy;
