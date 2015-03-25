%%%%%%%%%%%%%%%%%%%%%%判断一个值在向量中是否存在%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%val_i     一个值
%mat_vec   行向量
%val       返回值：0  表示不存在，1  表示存在
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