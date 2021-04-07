//////////////////  打印函数
function log(){
    try{
        console.log.apply(console, arguments);
    } catch (e){

    }
    try{
        print.apply(print, arguments);
    } catch (e){

    }
};
/*
var b = [1,2,3,4,5,6];
log('b is :',b);

////////////    强制转换

//string
var a = false.toString();
log('a is :',a);
var a = String(b);
log('a1 is :',a);

//数字,较于Number 使用parse 更加灵活
var c =Number(true);//
log('Number c is :',c);

var c = parseInt(false);
log('parseInt c1 is :',c);

var c = parseFloat("3.14159");
log('parseFloat c2 is :',c);

var c = parseInt(true);
log('parseInt c4 is :',c);


var d = b.valueOf()
log('valueOf d is :',d);
*/

var matrix = [[1,2,3],[4,5,6],[7,8,9]];
log('matrix is :',matrix);
log("matrix 2 1 is :",matrix[2][1]);
