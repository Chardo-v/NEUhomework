clear;
pic = imread('����ҵ.png');
pic1 = rgb2gray(pic);
pic2 = histeq(pic1);    %ֱ��ͼ���⻯

pic3 = im2bw(pic1);     %��ֵ������������β�Ϊ0�ڣ��������Ϊ1��
%pic3 = medfilt2(h);                       %�Խ���������ֵ�˲�
pic4 = imfill(pic3,'holes');   %���ڵ㣬��Ϊ�����ڲ�1�׺������ⲿ0��
[width, height] = size(pic4);   %ͼ��ָ0Ϊ��
for i=1:width
    for j=1:height
        if(pic4(i,j)==1)            %��ֵ��ɫ����,������Ϊ�߽���ڲ�
            if(pic3(i,j)==0)        %
                pic7(i,j)=pic1(i,j);
                pic5(i,j)=255;
                pic6(i,j)=255;
            else
                pic5(i,j)=pic1(i,j);    %
                pic6(i,j)=255;          %�ⲿ����
                pic7(i,j)=255;
            end
        else
            pic6(i,j)=pic1(i,j);
            pic5(i,j)=255;
            pic7(i,j)=255;
        end
    end
end

se = strel('disk',6);
pic8 = imerode(pic7,se);%
pic9 = imerode(pic8,se);%
se = strel('disk',7);
pic10 = imdilate(pic9,se);%
pic11 = imdilate(pic10,se);%

%�м䲿��Ч�����ã�����ԭͼ
[height, width] = size(pic7);
for i=1:height
    for j=1:width
        if((i>(height/2-40)&&i<(height/2+40))&&(j>(width/2-40)&&j<(width/2+40)))
            m(i,j)=pic7(i,j);
        else
            m(i,j)=pic11(i,j);
        end
    end
end

figure;
subplot(2,2,1);imshow(pic1,[]);title('����ǰ��');
subplot(2,2,2);imhist(pic1);title('�Ҷ�ֱ��ͼ��');
subplot(2,2,3);imshow(pic2,[]);title('ֱ��ͼ���⻯��');
subplot(2,2,4);imhist(pic2);title('ֱ��ͼ���⻯���ͼ��');

figure;
subplot(221);imshow(pic4,[]);title('�����ⲿ���ڲ��ֽ磺');
subplot(222);imshow(pic3,[]);title('�����ⲿ���ڲ����β������֣�');
subplot(223);imshow(pic5,[]);title('���壺');
subplot(224);imshow(pic7,[]);title('�β���');

figure;
subplot(221);imshow(pic7,[]);title('�β���');
subplot(222);imshow(pic9,[]);title('��һ��������ͼ��');
subplot(223);imshow(pic11,[]);title('�ڶ������ٸ�ʴͼ��');
subplot(224);imshow(m,[]);title('�м䲿�֡�ճ����������ԭ��');

image = edge(m,'log',4);
se = strel('disk',1);
pic11 = imdilate(image,se);%����.�߽��߸�����
% figure;
% imshow(pic11,[]);
[height, width, floor] = size(pic);
for i=1:height
    for j=1:width
        if(pic11(i,j)==1)
            picc(i,j,1)=255;
            picc(i,j,2)=0;
            picc(i,j,3)=0;
        else
            for k=1:floor
                picc(i,j,k)=pic(i,j,k);
            end
        end
    end
end
figure;
imshow(picc,[]);title('�β���');

