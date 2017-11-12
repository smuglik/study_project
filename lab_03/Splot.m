function Splot(LAMBDA, x1, y1, x2, y2)
    image_pull = dir('C:\temp\SpectralDeltaE\*.tif');
    if (isempty(image_pull))
        error('Check path to images');
    end
    image_count = length(image_pull);
    
    pix = zeros(2, image_count);
    
    clear image
    for i = 1:image_count
        image = imread(strcat('C:\temp\SpectralDeltaE\', image_pull(i).name));
        pix(1,i) = image(y1, x1);
        pix(2,i) = image(y2, x2);
    end
    figure;
    plot(LAMBDA, pix);
    xlabel('\lambda');
    ylabel('S');
end