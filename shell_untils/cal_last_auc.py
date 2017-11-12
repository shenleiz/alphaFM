# -*- coding: utf-8 -*- 
'''
Created on 2017年9月8日

@author: thinkpad
'''
from sklearn import metrics
import time 
import sys
y_test=[]
pred=[]
with open(sys.argv[1],'r') as r:
    for i in r.readlines():
        info = i.rstrip().split(' ')
        label = info[0]
        tmp_pred=float(info[1])
        if label=='1':
            y_test.append(1)
        else:
            y_test.append(0)
        pred.append(tmp_pred)
        
y_test=y_test[-8000000:]     
pred=pred[-8000000:]
fpr, tpr, thresholds = metrics.roc_curve(y_test, pred)
auc = metrics.auc(fpr, tpr)        
print 'end',time.ctime(),'auc:',auc  
if __name__ == '__main__':
    pass