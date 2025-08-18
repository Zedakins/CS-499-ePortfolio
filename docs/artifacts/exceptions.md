---
title: "Artifact — Exceptions (C++)"
layout: default
---

{% include nav.html %}

# Artifact — Exceptions (C++)

**Original (before):** [Go to Original Artifact](https://github.com/Zedakins/CS-499-ePortfolio/tree/main/original_artifact)
**Enhanced (after):** [Go to Enhanced Artifact](https://github.com/Zedakins/CS-499-ePortfolio/tree/main/enhanced_artifact) 

## Brief Description
The artifact began as a single-file C++ program (`Exceptions.cpp`) that demonstrated exception handling, including custom exceptions, standard exceptions, and division-by-zero detection. It was later enhanced into a modular, testable, and persistent application.

## Why Included
Exception handling is a foundational skill for all software engineers. This artifact was chosen because it shows my ability to grow a simple program into a professional-level project that spans three critical areas:  
- **Software Design & Engineering** — modular refactor, unit testing, CI, logging  
- **Algorithms & Data Structures** — batch processing pipeline with O(n) complexity  
- **Databases** — SQLite persistence with secure parameterized queries  

## Enhancements & Skills Demonstrated
- **Software Design & Engineering**
  - Refactored into multiple modules (`Exceptions`, `Logger`, `DB`, `BatchProcessor`)
  - Added documentation, tests, and CI workflows
- **Algorithms & Data Structures**
  - Created a batch processor that handles division tasks efficiently
  - Applied structured data (`DivisionTask → DivisionResult`) and complexity analysis
- **Databases**
  - Designed schema `ExceptionsLog`
  - Implemented secure inserts and retrieval using SQLite

## Evidence & Outcomes
- **Tests:** All unit tests pass (target coverage ≥ 80%)  
- **Performance:** Batch processing scales linearly with input size  
- **Database:** Exception events can be persisted and retrieved reliably  

## Reflection
Enhancing this artifact showed me how modularization improves maintainability, how algorithmic design decisions affect scalability, and how database integration introduces persistence and security. I faced challenges when integrating SQLite, particularly around memory management and parameter binding, but overcame them through research and iteration. This process reinforced my ability to learn independently and apply new technologies in a structured way.

## Course Outcomes Met
- **Software design & engineering:** Fully met  
- **Algorithms & data structures:** Fully met  
- **Databases:** Fully met  
- **Security considerations:** Met (parameterized queries, safe exception handling)  
- **Collaboration/communication:** Partially met (primarily individual enhancement but with clear documentation and structured code)
