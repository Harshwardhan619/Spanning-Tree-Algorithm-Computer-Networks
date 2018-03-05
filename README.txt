Roll nunmber: 160050048

	I was only able to complete the first part of the assignment i.e. To make a spaaning tree out of given graph.
	
	Algorithm used:
	
	1. Take input and store it in data structure (in my case: a vector of bridges) with default values (all are root bridges).
	2. From these bridges, find the bridge with smallest value (say Bsmallest).
	3. Generate/Forward messages.
	4. Process the messages on the LANs as follows (LANs are used to assign port NP)
		A port is assigned NP when comparing messages from two links if
			a. both two messages root bridges (Bsmallest) are same but there distance differs. NP is assigned to the links whose distance id higer.
			b. if both root-bridge (Bsmallest) and distance is same from both messages, then asiigned NP to the next-hop having higher value.
	5. Forward these message to all bridges except from where they come and NP links.
	6. After processing at LANs, process messages at all the bridges.
		Now DP, RP is assigned to a port using the standard method.
		compare all messages recieved from all sites and compare to assigne DP or RP to the remaining ports(port not assigned NP)
			RULES to assign RP;
			a. Message with smaller root value.
			b. IF root same then message with less distance.
			c. if root same and distances are same then compare the next hop bridge with lower value.

	
	I have done some part of forwarding table making bi=ut its not giving any output as its not complete.
