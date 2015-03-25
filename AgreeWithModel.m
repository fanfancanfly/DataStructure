%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%��������ģ�͵��ж���,ͨ���㵽�ߵľ������ж�%%%%%%%%%%%%%%%%%%%%%%%%%
%Consensus_Setx     ԭ����x���ڵ�
%Consensus_Sety     ԭ����y���ڵ�
%Maybe_outliersx    x�����
%Maybe_outliersy    y�����
%line_vec           ֱ�ߵ�ϵ��
%point_line_dis     �㵽ֱ�ߵľ�����ֵ
function [Re_Consensus_Set2d,Re_Consensus_Set3d] = AgreeWithModel(Consensus_Setx,Consensus_Sety,Maybe_outliersx,Maybe_outliersy,line_vec,point_line_dis)
Consensus_Set_temx = Consensus_Setx;                %��ʱ�������б���
Consensus_Set_temy = Consensus_Sety;
[m,n] = size(Maybe_outliersx);
for i=1:m
    distem = abs(line_vec(1,1)*Maybe_outliersx(i,1)+line_vec(1,2)-Maybe_outliersy(i,1))/sqrt(line_vec(1,1)^2+1);           %�жϵ㵽ֱ�ߵľ���
    if (distem < point_line_dis)
        Consensus_Set_temx = [Consensus_Set_temx;Maybe_outliersx(i,1)];
        Consensus_Set_temy = [Consensus_Set_temy;Maybe_outliersy(i,1)];
    end
end
Re_Consensus_Set2d = Consensus_Set_temx;
Re_Consensus_Set3d = Consensus_Set_temy;
