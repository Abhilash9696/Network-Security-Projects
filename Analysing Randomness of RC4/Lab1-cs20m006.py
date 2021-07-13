import math
import random
import pandas as plt 
import plotly.graph_objects as obj
S = [0]*256
T = [0]*256 
# Defining two stages of RC4: 1.KSA and 2.PRGA functions
def KSA(Key):
  key_length = int(len(Key)/8) 
 
 #intialising S
  a = 0
  while a < 256:
    S[a] = a
    a = a + 1
  
  #initialising T
  k = 0
  while k < 256:
    t = 0
    j = 0
    while j < 8:
      t = t + int((Key[k*8 + j])*(2**j))
      j = j+1
    T[k] = t
    k = k + 1
  
  #Swapping values of S
  i = 0 
  for j in range(256):
    i = (i + S[j] + T[j]) % 256
    temp = S[i]
    S[i] = S[j]
    S[j] = temp

  
  #Generating psuedo random key stream that is used to encrypt.
  #We are only using this key stream to check the randomness variation with bits toggling but not actual encryption
def PRGA(b):
    i = 0
    j = 0
    temp1 = [0]*b
    t = 0
    while t<b and i<256 :
          i = (i + 1)%256
          j = (j + S[i])% 256
          temp2 = 0
          temp2 = S[i]
          S[i] = S[j]
          S[j] = temp2
          temp1[t] = S[(S[i] + S[j])% 256]
          t = t + 1
    return temp1

# randomly toggles bits b/w the indices 1 to 2048 based on the j random numbers in random list we generate
def toggle_bits(a,j,l):
  key1 = ""                    
  c=-1
  r_list = random.sample(range(l, 2048), j)
  for i in a:
    c +=1
    if c not in r_list: 
      key1 += i
    else:
      if i == '0':
        key1 += '1'
      else:
        key1 +='0'
  return key1
p2 = plt.DataFrame(columns=["bits"], index = range(1,33))
for i in range(1,33):
    p2.loc[i,'bits'] = i



if __name__ == "__main__":

  no_of_bytes = [2,8,32,64,128,256,512] #cypher block size in bytes
  for p in no_of_bytes:
    print("Starting Calculation for rc4 keystream size :",p," started")    
    for j in range(1,33):
      l1 = 0
      l2 = 0
      c2 = [0]*256               #counter1 is initialised for every bit toggled
      for l in range(40):
        
        #Generating a 2048 bit key
        k1 = ""
        for i in range(2048):
            k1 = k1 + str(random.randint(0, 1))
        k2 =toggle_bits(k1,j,0)        #toggles j bits of key k1            
        #k3=toggle_bits(k1,j,1024)      #toggles j bits of key k1 starting from 1024th bit   
        
        
        
        #Performing rc4 algorithm on the above 3 keys by calling Key Scheduling Algorithm (KSA function) 
        #and Pseudo Random Generation Algorithm (PRGA function) in order.    
        KSA(k1) 
        k1_rc4 = PRGA(p) #rc4 key stream generation using k1 as initial key

        KSA(k2) 
        k2_rc4 = PRGA(p) #rc4 key stream generation using k2 as initial key
        
        '''KSA(k3) 
        k3_rc4 = PRGA(p) #rc4 key stream generation using k3 as initial key'''
        
        
        #converting k1_rc4 to binary
        k1_rc4_bin = ''
        for i in k1_rc4:
          bin_key = ''
          D = bin(i)[2:]
          for m in range(2+6-len(D)):
            bin_key += '0'
          k1_rc4_bin += bin_key + D
        
        #converting k2_rc4 to binary
        k2_rc4_bin = ''
        for i in k2_rc4:
          bin_key = ''
          D = bin(i)[2:]
          for m in range(2+6-len(D)):
            bin_key += '0'
          k2_rc4_bin += bin_key + D
        
        '''#converting k3_rc4 to binary
        k3_rc4_bin = '' '''
        '''for i in k3_rc4:
          bin_key = ''
          D = bin(i)[2:]
          for m in range(2+6-len(D)):
            bin_key += '0'
          k3_rc4_bin += bin_key + D'''
        #Counter values are being updated           
        for i in range(len(k1_rc4_bin)-7):
          A=k1_rc4_bin[i:i+8]
          B=k2_rc4_bin[i:i+8]
          #C=k3_rc4_bin[i:i+8]
          temp=0
          for i in range(8):
            if A[i] == B[i]:
              temp = 2*temp
            else:
              temp = 2*temp+ 1
          t = temp
          c2[t] = c2[t] + 1      


        tsum = 0
        for i in range(256):   
            tsum = tsum + c2[i]
        mean2 = tsum / 256
        temp = 0
        for i in range(256):  
          temp = temp + (c2[i]-mean2)**2
        sd2 = math.sqrt((1/256.0)*temp)
        l2 = l2 + (sd2 * 256 / (8*p-7))
      p2.loc[j,str(p)] = l2/40 
print("p2:",p2)

print("plotting now" )
fig = obj.Figure()
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['2'],
                    mode='lines+markers',name='2B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['8'],
                    mode='lines+markers', name='8B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['32'],
                    mode='lines+markers', name='32B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['64'],
                    mode='lines+markers', name='64B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['128'],
                    mode='lines+markers', name='128B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['256'],
                    mode='lines+markers', name='256B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['512'],
                    mode='lines+markers', name='512B'))


fig.update_layout(title='graph1:Bits are randomly toggled between the indices 1 and 2048',
                   xaxis_title='Bits toggled',
                   yaxis_title='Randomness')


fig.show()

'''fig = obj.Figure()
fig.add_trace(obj.Scatter(x=p1['bits'], y=p1['2'],
                    mode='lines+markers',
                    name='2B'))
fig.add_trace(obj.Scatter(x=p1['bits'], y=p1['8'],
                    mode='lines+markers', name='8B'))
fig.add_trace(obj.Scatter(x=p1['bits'], y=p1['32'],
                    mode='lines+markers', name='32B'))
fig.add_trace(obj.Scatter(x=p1['bits'], y=p1['64'],
                    mode='lines+markers', name='64B'))
fig.add_trace(obj.Scatter(x=p1['bits'], y=p1['128'],
                    mode='lines+markers', name='128B'))
fig.add_trace(obj.Scatter(x=p1['bits'], y=p1['256'],
                    mode='lines+markers', name='256B'))
fig.add_trace(obj.Scatter(x=p2['bits'], y=p2['512'],
                    mode='lines+markers', name='512B'))


fig.update_layout(title='graph2: Bits toggled are in range 1 to 2048',
                   xaxis_title='Bits toggled',
                   yaxis_title='Randomness')'''


##fig.show()




