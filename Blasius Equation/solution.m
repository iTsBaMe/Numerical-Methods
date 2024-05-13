clear all;
close all;
clc;
guess1 = 0.1;
guess2 = 1;

err_threshold = 1e-3;
iterator = 1
err =1 ;
while err > err_threshold
    if iterator == 1
        [eta,f ] = ode45(@myfunc,[0,10],[0;0;guess1]);
        m1 = f(end,2);
        [eta,f ] = ode45(@myfunc,[0,10],[0;0;guess2]); 
        m2 = f(end,2);

    else
        guess2 = (guess2-guess1)/(m2-m1)*(1.0-m1)+guess1;
        [eta,f ] = ode45(@myfunc,[0,10],[0;0;guess2]); 
        m2 = f(end,2);
        err = abs(1-m2);
    end
    iterator = iterator +1;
end
plot(f(:,1),eta,'-r',f(:,2),eta,'-b',f(:,3),eta,'-g');
title('Solution of blasius equation using ODE45');
xlabel('f');
ylabel('\eta');
legend('f1','f2','f3');

%the desired solution for the initial condition
%is such that x2(end,2) =1



