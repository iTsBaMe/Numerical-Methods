%nan means not a number infinity
%secant method is used when newton rhapson method fails
%always converge
%doesnt fail which means it doesnt need any if else condition

f = input('Enter your function: \n');
x0 = input('Enter your first initial guess: \n');%even if we change the initial values the method doesnt diverge 
x1 = input('Enter your second initial guess: \n');
e= input('Enter the tolerance: \n');;
n= input('Enter the number of iterations: \n');
xlabel('Iteration');
ylabel('Roots')
title('Plot between Roots vs Iteration')
grid on;
hold on;
%processing
for i=1:n;
    x2 = (x0*f(x1)-x1*f(x0))/(f(x1) -f(x0));
    
    fprintf('X%d = %.4f\n' ,i, x2) %x6 and x7 have same values and their difference is 0 resulting in infinity of x8,9 and 10
    t(i) = i;
    x(i)  =x2;
    if abs(x2-x1)<e %depends on tolerance
        break
    end
    x0=x1;%x0 is being replaced by x1
    x1=x2;%order cant be change otherwise x0 and x1 will be same

    plot(t,x,'r','Linewidth', 3) %x-axis = t and y-axis = roots
end


%in the given function no root exist between -2 and -1
%but secant method doesnt depend on the initial values
%SECANT METHOD NEVER FAILS


