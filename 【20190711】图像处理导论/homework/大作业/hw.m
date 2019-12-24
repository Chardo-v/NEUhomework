clear;
img = imread('����ҵ.png');
%��Ŀ1��תΪ�Ҷ�ͼ������imhist���ֱ��ͼ
img1 = rgb2gray(img);
%��Ŀ2�����⻯����
img2 = histeq(img1);
%�����Ŀ1��2�Ľ��
figure;
subplot(2,2,1);imshow(img1,[]);title('T1:����ǰ��');
subplot(2,2,2);imhist(img1);title('T1:�Ҷ�ֱ��ͼ��');
subplot(2,2,3);imshow(img2,[]);title('T2:���⻯��ͼ��');
subplot(2,2,4);imhist(img2);title('T2:���⻯��ֱ��ͼ��');

%��Ŀ3��
%�Ҷ�ͼ���ֵ��
img3 = im2bw(img1);
%ͼ����䣬�����ڲ�Ϊ1���ⲿΪ0
img4 = imfill(img3,'holes');
%ͼ����ηָ�ԡ�����-��硱�͡��β�-���塱Ϊ��������
[width, height] = size(img4);
for i=1:width
    for j=1:height
        if(img4(i,j)==1)
            if(img3(i,j)==0)
                img7(i,j)=img1(i,j);
                img5(i,j)=255;
                img6(i,j)=255;
            else
                img5(i,j)=img1(i,j);
                img6(i,j)=255;
                img7(i,j)=255;
            end
        else
            img6(i,j)=img1(i,j);
            img5(i,j)=255;
            img7(i,j)=255;
        end
    end
end
figure;
subplot(221);imshow(img3,[]);title('T3:�����֣�');
subplot(222);imshow(img4,[]);title('T3:������');
subplot(223);imshow(img7,[]);title('T3:��ʵ�ʣ�');
subplot(224);imshow(img5,[]);title('T3:������֯��');

%��Ŀ4��
%ȥ���β��еİ�ɫС���
se = strel('disk',6);
img8 = imerode(img7,se);
%����ͼ��
img9 = imerode(img8,se);
se = strel('disk',7);
img10 = imdilate(img9,se);
%��ʴͼ��
img11 = imdilate(img10,se);
%ճ��ͼ��
[height, width] = size(img7);
for i=1:height
    for j=1:width
        if((i>(height/2-40)&&i<(height/2+40))&&(j>(width/2-40)&&j<(width/2+40)))
            m(i,j)=img7(i,j);
        else
            m(i,j)=img11(i,j);
        end
    end
end
image = edge(m,'log',4);
se = strel('disk',1);
img11 = imdilate(image,se);
figure;
imshow(img11,[]);title('T4:�β���');
imwrite(img11,'resultT4.jpg');

%��Ŀ5��ѹ��ͼ��
I = img11;
I = im2double(I); % ��������ת��
T = dctmtx(8); % �����ά��ɢDCT����
dct = @(x)T * x * T'; % ���ú������
B = blkproc(I,[8 8],dct); % ͼ��鴦��
mask = [1 1 1 1 0 0 0 0 % ��Ĥ
1 1 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0];
B2 = blkproc(B,[8 8],@(x)mask.* x); % ͼ��鴦��
invdct = @(x)T' * x * T; % ���ú������
I2 = blkproc(B2,[8 8],invdct); % ͼ��鴦��
figure, imshow(I2),title('T5:ѹ����ѹ���ȣ�72.20%��'); % ��ʾԭʼͼ���ѹ���ع�ͼ��
imwrite(I2,'resultT5.jpg');