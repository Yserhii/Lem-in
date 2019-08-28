# Lem-in

How to start:
```bash
git clone https://github.com/Yserhii/Lem-in.git && cd Lem-in && make
```

<div align="center">
  <img src="https://github.com/Yserhii/Lem-in/blob/master/sourses/Part_1.png" width="100%" />
</div>

## How use:
- ./generator --help
- ./lem-in --help
- ./lem-in < map

## What this is
This is a school project about graph traversal, flow regulation, ants, and more.

The program takes as input an anthill, which looks like this:
```
15                <-  Number of ants.
3 100 500         <-  Room name, followed by its x-y coordinates.
##start           <-  Special room "start", the source of our flow.
start 200 300
##end             <-  The other special room, our sink.
end 250 900
4 100 700
1 200 500
2 200 700
5 300 500
6 300 700
start-1           <-  "start" room is connected to the "1" room.
3-4               <-  "3" is connected to "4", and so on.
2-4
1-5
6-5
end-6
1-2
2-end
3-start
```
From there, it computes the most efficient way to move all the ants from *start* to *end*, with the proviso that ants can't step on each other, i.e. you can't have two ants in one room at the same time.
The program will output this solution for the above anthill:
```
L1-1 L2-3
L1-5 L2-4 L3-1 L4-3
L1-6 L2-2 L3-5 L4-4 L5-1 L6-3
L1-end L2-end L3-6 L4-2 L5-5 L6-4 L7-1 L8-3
L3-end L4-end L5-6 L6-2 L7-5 L8-4 L9-1 L10-3
L5-end L6-end L7-6 L8-2 L9-5 L10-4 L11-1 L12-3
L7-end L8-end L9-6 L10-2 L11-5 L12-4 L13-1 L14-3
L9-end L10-end L11-6 L12-2 L13-5 L14-4 L15-1
L11-end L12-end L13-6 L14-2 L15-5
L13-end L14-end L15-6
L15-end
```
`L2-3` means "ant number 2 goes to room number 3." Each line of output corresponds to one "round" of moving ants through the anthill. The goal is to choose paths optimally to minimize this number of lines.
