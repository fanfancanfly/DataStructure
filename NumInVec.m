%%%%%%%%%%%%%%%%%%%%%%�ж�һ��ֵ���������Ƿ����%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%val_i     һ��ֵ
%mat_vec   ������
%val       ����ֵ��0  ��ʾ�����ڣ�1  ��ʾ����
function   val = NumInVec(val_i,mat_vec)
[m,n] = size(mat_vec);
max_val =n;
val_tem =0;
for i=1:max_val
    if (val_i == mat_vec(1,i))
        val_tem = 1;
    end
end
val = val_tem;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%