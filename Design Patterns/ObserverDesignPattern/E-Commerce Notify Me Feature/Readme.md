# 🛒 E-commerce Stock Notification System (LLD)

## 🎯 Problem Statement

Design a **“Notify Me When Product is Back in Stock”** feature for an e-commerce platform.

---

## ✅ 1. Functional Requirements

- Users can subscribe to a product when it is out of stock
- Users get notified when the product is restocked
- Multiple users can subscribe to the same product
- Users can unsubscribe

---

## ⚙️ 2. Non-Functional Requirements

- Scalable to many products
- Decoupled notification system
- Extensible (Email, SMS, Push, etc.)
- Safe memory handling (no leaks)

---

## 🧠 3. Design Pattern Used

**Observer Pattern**

- **Observable (Subject)** → Product
- **Observers** → Notification subscribers (Email / Push / SMS)

---

## 🧩 4. Class Design

### 1. StockAvailabilityObservable (Interface)

- `addObserver()`
- `removeObserver()`
- `notifyObservers()`
- `purchase()`
- `restock()`

---

### 2. StockNotificationObserver (Interface)

- `update()`
- `getUserId()`
- `getNotificationMethod()`

---

### 3. Product (Concrete Observable)

- Holds product data
- Maintains list of observers
- Triggers notification on restock

---

### 4. Concrete Observers

- `EmailNotificationObserver`
- `PushNotificationObserver`

---

## 📊 5. UML Class Diagram

+----------------------------------+<br>
| StockAvailabilityObservable |<br>
+----------------------------------+<br>
| +addObserver() |<br>
| +removeObserver() |<br>
| +notifyObservers() |<br>
| +purchase() |<br>
| +restock() |<br>
+----------------------------------+<br>
▲<br>
|<br>
|<br>
+----------------------------------+<br>
| Product |<br>
+----------------------------------+<br>
| - productId |<br>
| - productName |<br>
| - price |<br>
| - stockQuantity |<br>
| - observers (weak_ptr list) |<br>
+----------------------------------+<br>
| +addObserver() |<br>
| +removeObserver() |<br>
| +notifyObservers() |<br>
| +purchase() |<br>
| +restock() |<br>
+---------------<br>-------------------+<br>
|<br>
▼<br>
+------------------------------------------+<br>
| StockNotificationObserver |<br>
+------------------------------------------+<br>
| +update() |<br>
| +getUserId() |<br>
| +getNotificationMethod() |<br>
+------------------------------------------+<br>
▲ ▲<br>
| |<br>
+----------------------+ +----------------------+<br>
| EmailNotification | | PushNotification |<br>
+----------------------+ +----------------------+<br>
| - email | | - deviceToken |<br>
+----------------------+ +----------------------+<br>
| +update() | | +update() |<br>
+----------------------+ +----------------------+<br>

---

## 🔄 6. Sequence Flow

### Scenario: Product Out of Stock → Restocked

User → Product : purchase() <br>
Product → User : Out of stock <br>
User → Product : addObserver()<br>
Admin → Product : restock()<br>
Product → notifyObservers()<br>
Product → Observer1 : update()<br>
Product → Observer2 : update()<br>

---

## 🧠 7. Key Design Decisions

### ✅ Generic Product Class

- Avoids product-specific classes (e.g., IphoneProduct)
- Scales across entire catalog

---

### ✅ weak_ptr for Observers

- Prevents memory leaks
- Avoids circular dependencies

---

### ✅ Decoupled Notification Logic

- Product doesn’t handle notification details
- Observers manage delivery mechanism

---

### ✅ Safe Iteration During Notification

- Avoids concurrent modification issues

---

## ⚠️ 8. Limitations

- In-memory storage of observers
- Data lost on service restart
- Not suitable for distributed systems
- Not scalable to millions of users

---

## 🚀 9. Real-World Extension (High-Level Design)

Replace in-memory observer model with event-driven architecture:

Product Restocked<br>
↓<br>
Event (Kafka / RabbitMQ)<br>
↓<br>
Notification Service<br>
↓<br>
Fetch subscribers from DB<br>
↓<br>
Send Email / Push / SMS<br>

---

## 🔥 10. Interview Explanation

> I used the Observer Pattern where Product acts as the subject and users act as observers. When stock becomes available, all subscribed users are notified. I used weak pointers to avoid memory leaks and ensure safe memory management. For scalability, I would replace in-memory observers with an event-driven system and persist subscriptions in a database.

---

## 🧩 11. Follow-up Questions

### Q: How to make it thread-safe?

- Use mutex for observer list

### Q: How to persist subscriptions?

- Store `(userId, productId)` in database

### Q: How to avoid duplicate notifications?

- Maintain notification state per user

### Q: How to scale to millions of users?

- Use async processing + message queues

---

## 🏁 Summary

- Pattern Used → Observer Pattern
- Core Entity → Product
- Subscribers → Notification Observers
- Scalable Version → Event-driven architecture

---
