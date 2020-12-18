close all; clear; clc;

im = imread('./src/lena.jpg');

if ~exist('time_elapased.mat', 'file')

    % time test
    step = 3;
    radius = 1:step:30;
    run_times_median = zeros(length(radius), 1);
    idx = 1;
    for r = radius
        win = r*2+1;
        time_start = tic;
        for i = 1:10
            result1(:,:,1) = medfilt2(im(:,:,1), [win, win]);
            result1(:,:,2) = medfilt2(im(:,:,2), [win, win]);
            result1(:,:,3) = medfilt2(im(:,:,3), [win, win]);
        end
        time_elapased = toc(time_start);
        run_times_median(idx) = time_elapased/10;
        idx = idx + 1;
    end
    run_times_sidewindow = zeros(length(radius), 1);
    idx = 1;
    for r = radius
        time_start = tic;
        for i = 1:10
            result2 = SideWindowBoxFilter(im, r, 1);
        end
        time_elapased = toc(time_start);
        run_times_sidewindow(idx) = time_elapased/10;
        idx = idx + 1;
    end
    save('time_elapased.mat', 'run_times_median', 'run_times_sidewindow', 'radius')
else
    load time_elapased.mat
end

% plot
plot(radius, run_times_median*1000, 'LineWidth', 1.1)
hold on,
plot(radius, run_times_sidewindow*1000, 'LineWidth', 1.1)
legend('median', 'sidewindow')
xlabel('窗口半径, Half Radius')
ylabel('耗时(毫秒), Time Elapased(ms)')
ax = gca;
outerpos = ax.OuterPosition;
ti = ax.TightInset;
left = outerpos(1) + ti(1);
bottom = outerpos(2) + ti(2);
ax_width = outerpos(3) - ti(1) - ti(3);
ax_height = outerpos(4) - ti(2) - ti(4);
ax.Position = [left bottom ax_width ax_height];

set(gca, 'color', 'none');
fig_rgb = getframe(gcf);
fig_rgb = fig_rgb.cdata;
alpha = ones(size(fig_rgb, 1), size(fig_rgb, 2));
fig_gray = rgb2gray(fig_rgb);
alpha(fig_gray==240) = 0;
imwrite(fig_rgb, 'time_elapased_cmp.png', 'Alpha', alpha);
