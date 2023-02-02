# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- Diego Garcia
- team member 2

## Lab Question Answers

Answer for Question 1: 
I observed missing information while sending data. The issue became more pronounced when I continously sent large amounts of data to the server. This is because UDP uses a "best effort" approach, meaning it attempts to transfer data but does not guarantee its successful delivery. Any lost data cannot be recovered.

Answer for Question 2:
The dependability of TCP remained consistent, as all the data I sent was eventually received and displayed on the terminal. This is due to TCP's protocol for recering lost data. If any data is not received, it will continously attempt to retrieve it until it is confirmed as received.

Answer for Question 3:
The responsiveness of TCP varied, sometimes it was prompt and there was no apparent data loss, and at other times it took multiple seconds for me to receive the data I had previously sent. This was particularly noticeable when I repeatedly sent large amounts of data to the server, it took much longer for me to receive all the data.
