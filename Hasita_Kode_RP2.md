# The TSEC/KW-26: History and Development

Hasita Kode
Summer 2026 
McAlpin Security in Computing

## I. Introduction

The purpose of this report is to analyze the history of the design, development, and deployment of 
the TSEC/KW-26, the first mass produced electronic encryption device by the United States government
for teletypewriter communications.

Before the KW-26 existed, most secure record traffic relied either on one time paper take systems or
on electro mechanical rotor machines, both of which carried heavy operational burdens in production, 
distribution, and destruction of key material [1, p.3]. The National Security Agency [NSA], formed in 
1952 out of the merger of the individual service cryptologic agencies, inherited the mission of 
protecting record communications for the entire defense and intelligence community, and it was under 
this mandate that the KW-26 was conceived [1, p.4]. What followed was a multi year effort that fused 
newly emerging logic with old cryptographic theory, ultimately creating a machine that would secure
American teletype traffic for almost 25 years. 

## II. History of Development

### A. Sponsor and Creator Identification

The KW-26 program was sponsored internally by the NSA's Record and Data group, led by Howard Barlow, 
following the 1949 merger of the Army Security Agency and Naval Security Group into what would eventually
become the NSA in 1952 [1, p.4] . Engineering work was carried out by an in-house team, including Joe 
Hannan and Vern Zeigler, who build an experimental vacuum tube proof of concept, while the production 
grade design was ultimately contracted out to the Burroughs Corporation starting in 1953 [1, p5-6].

### B. Motivation

Barlow's group was tasked with finding an on line replacement for the British 5-UCO system, which 
the intelligence community had relied on for high frequency radio links but which demanded enormous 
volumes of one time key tape to run continuously [1, p.4]. Barlow framed the goal plainly: the new equipment 
needed to be inexpensive and unobtrusive that it would never become a operational [1, p.4]. Just as 
important, whatever replaced the 5-UCO had to preserve its traffic flow security, meaning that outside
observers monitoring the circuit could not tell when real message traffic was present. 

### C. Technology Selection Rationale

At the time these requirements were drawn up, the miniature vacuum tube was the most mature electronic
technology available, but it suffered from reliability and power problems, and the transistor, though
already invented, was still years away from practical use [1, p.5]. The breakthrough came through an 
external contact: an NSA engineer learned that a former classmate at the Burroughs Corporation Research
Center was experimenting with bi-stable magnetic cores, called BIGMAG, which could implement binary logic
and shift registers without the drawbacks of tubes [1, p.5]. This informal exchange between NSA and 
Burroughs engineers grew into a formal research relationship and eventually a sole source development 
contract in 1953, in which Burroughs proposed building the entire cryptologic design, from the Fibonacci 
shift register down to the combining logic, out of BIMAG cores [1, p.6]. 

## III. Development Timeline and Operational Trials

### A. Engineering Development

Burroughs delivered its first BIGMAG-based model in 1955, proving that magnetic cores could outperform 
vacuum tubes on both reliability and power draw, even though the cores were still hand wired onto exposed 
circuit boards [1, p6-7]. A follow on contract that same year addressed the obvious next problem, which was
 packaging: engineers potted each core into a sealed module with twelve modules onto large multilayer boards, 
 five of which made up a complete transmitter or receiver [1, p.7]. Customer evaluation units went out in 
 1957, but early environmental testing uncovered a temperature related failure in the ceramic capacitors, which
 was eventually traced to a bad manufacturing batch and resolved through new incoming inspection procedures [1, p.8].


 ### B. Operational Trails

Final engineering units were tested on the CRITICOMM network, the communications backbone supporting the 
network, the communications backbone supporting the national signals intelligence mission, and performed well 
overall except for one persistent weakness: unlike the 5-UCO, the KW-26 had no way to "walk" the key stream 
forward or backward to compensate for shifting transmission delays [1, p.8]. NSA solved this with an add on delay 
unit, the TSEC/HW-8, which let receive operators search for the correct synchronization point roughly ninety percent
of the time without forcing a full restart of the link [1, p.8]. 

## IV. Impact on Confidentiality, Integrity, and Availability

The kW-26 was built specifically to protect all three legs of what would later be formalized as the CIA 
triad. Confidentiality was the machine's main purpose: by modulo-2 combining plaintext with a key stream generated 
from punched key cards, it rendered intercepted teletype traffic unintelligible to anyone without the matching card, 
extending the mathematical guarantee behind Bilbert Vernam's original one-time tape cipher to an on line electronic
 device [1, p1-2]. Integrity was addressed through strict key management doctrine; the common fill device was designed
 so that a daily key card could not be reused, and the card was physically severed the moment the device was reopened, 
 preventing any deliberate or accidental replay of old key material [1, p.6]. Availability was supported through the 
 machine's traffic flow security feature, which kept the circuit continuously encrypted regardless of whether real 
 messages were being sent, denying an adversary any ability to disrupt operations by watching for gaps in traffic, 
 and through the HW-8 delay unit, which kept links running through synchronization problems rather than forcing lengthy 
 restarts [1, p.8]. 

 ## V. General Characteristics

 A single KW-26 transmitter or receiver contained more than eight hundred magnetic cores and roughly fifty 
 vacuum-tube driver circuits, filling a little over half of a standard equipment rack, with most of that space 
 and most of its one kilowatt of input power consumed by the tube circuitry needed to interface with the many different 
 communication formats the machine had to support [1, p.10]. Cryptographically, the system retained the modulo-2 "exclusive 
 or" combining technique that Vernam had patented in 1919, mixing a Fibonacci based key stream with plaintext to produce 
 cipher text, and preserved the parent 5-UCO's traffic flow security property, meaning it could be operated 
 continuously over ordinary commercial circuits [1, p2-4]. Because different services demanded so many transmission 
 modes and speeds, the design grew more complex than originally planned.. in practice, no more than 3 or 4 of 
 the many supported configurations ever saw real use, and one costly option build for the era's low speed transoceanic 
 cables ended up delaying production at the exact moment demand for the machine was highest [1, p.9]. 

 ## VI. Usage Domains

 The KW-26 became the primary encryption device on the CRITICOMM network, protecting both message content and traffic 
 patterns flowing between signals intelligence collection sites and NSA analyst [1, p.10]. It was also adopted 
 across the services in very different physical environments: the Navy installed it in shore facilities, and abroad ships, 
 where it had to survive the shock and vibration of sixteen inch gun fire, while the Army and Air Force used it for tactical 
 point to point links [1, p.11]. Beyond the military, the Defense Communications Agency relied on teh KW-26 as the 
 principal encryption for its AUTODIN message switching trunks, and both the CIA and the State Department deployed it on 
 their own point to point circuits, illustrating how a single NSA-sponsored design ended up securing traffic across the 
 entire defense and diplomatic [1, p.11]. 

 ## VII. Lifecycle and Legacy

 Counting from the 1953 development contract to the first production order in 1957, the KW-26 took roughly four years
to move from concept to fielded equipment, and the initial 1,500-unit order for CRITICOMM was followed by further
procurements through the early 1960s that eventually exceeded 14,000 total units across the services [1, p.10]. The 
system remained in active service for more than twenty-five years, spanning nearly the entire Cold War, before NSA began
decommissioning it in the mid-1980s in favor of the more advanced solid-state TSEC/KG-84 [1, p.11]. 
Decommissioning itself took several years and required returning sensitive components, primarily the printed circuit boards
and common fill devices that revealed the combining logic, for secure destruction, while the remaining hardware was
stripped of identifying labels and scrapped [1, p.12].

## VIII. Critical Analysis

The KW-26 program illustrates the risk of open ended, multi user requirements in a large acquisition. Because no since authority 
 within the Department of Defense or the intelligence community controlled the requirements process,
the equipment was repeatedly modified during development to accommodate operational conditions that had not been
anticipated at the outset, from shipboard gunfire vibration to a wide range of transmission speeds most of which were
rarely used in practice [1, p.11]. The program's own engineers concluded afterward that future efforts needed a much better
understanding of real user environments before writing specifications, along with a cleaner mechanism for folding in
engineering changes discovered during testing, and argued that the handoff from research and development to
production should aim to be, in their words, a "build to print" process [1, p.12]. That lesson still holds in
modern COMSEC and systems engineering practice more broadly: requirements volatility late in a hardware program
tends to compound cost and schedule risk far more than the same volatility would in software, precisely because physical
production and fielded key management cannot be patched after the fact.

## IX. Conclusion

The TSEC/KW-26 was the product of a fortunate convergence between an NSA research team with a clear cryptographic 
requirement and an industrial partner willing to gamble on an unproven magnetic core technology. It preserved the 
mathematical strength of the Vernam cipher while finally making on line electronic encryption practical for round the 
clock government use, and it went on to protect confidentiality, integrity, and availability of American record traffic 
across the Navy, Army, Air Force, CIA, and State Department for over a quarter century. Its retirement in the mid 1980s 
in favor of the KG-84 closed out one of the longest serving cryptographic systems in NSA history, but the acquisition lessons 
its engineers documented along the way remain directly relevant to COMSEC programs today. The KG-84 offered a more compact solid-state design, improved reliability, and modernized key management capabilities, making it a suitable successor to the aging KW-26.

## References
[1]M. Klein, Securing Record Communications :. 2003.

