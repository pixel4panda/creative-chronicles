# SPROUTFOLIO
#### Video Demo:
#### Description:
Ideally my app starts as a financial tracking app for myself. I am looking into the possibility of expanding it and letting friends try it out too.

I wanted it to have a plant theme, because I like plants. So I used a plant for a logo and tried to keep my colors to an earthy / green tone

---
## Table of Contents
- [Project Features](#project-features)
- [app.py](#apppy)
- [backend.py]
- [money_func.py]
- [Folder: templates](#folder-templates)
- [Folder: static](#folder-static)

---
## Project Features:

TODO 
- Add, edit, and delete transactions
- Categorize income and expenses
- Automatically update account balances and store them in a monthly history.
- Pagination for

#### Design Decisions:

In research I found that when handling money a common workaround it to use INTEGER instead of FLOAT to avoid rounding errors. So everything is multiplied by 100 when storing values and divided by 100 when displaying. 

**see money_func.py for further information*


---
## app.py

### Application Setup

Flask app configured with session support using `flask_session`.

Custom Jinja filters: `money` and `m_display`.

*The necessity for two different filters came from using money as an input, where only numbers are needed and using money as an information for the reader, where the '$' symbol is required for clear readability.*

All responses are configured to not cache `(after_request)`.

Database connection via `get_db()` and closed with `close_db()`.

>Authentication helper functions: `login_required`, `user_error`.  
>Libraries: `Flask`, `flask_session`, `sqlite3`, `werkzeug.security`

[Return to TOC](#table-of-contents)

### @index()  

This route redirects the user to the dashboard if they are already logged in, otherwise, it prompts the login page.  

It checks for a `user_id` in the session and redirects accordingly 

**Key Points:** 
1. Checks session to determine if user is logged in.  
2. Redirects to `/dashboard` for authenticated users.  
3. Redirects to `/login` for unauthenticated users.  

>Tables: None  
>Depends on: `redirect`, `session`

### @login()  

Handles user login: displays the login page on GET requests and processes authentication on POST requests.

On POST, it validates the submitted email and password, checks credentials against the database, and sets the session `user_id` on success. 

**Key Points:**  
1. Clears any existing session before login.  
2. Validates form inputs (`email`, `password`).  
3. Checks credentials against `users` table and sets `session["user_id"]`.  
4. Redirects to `/dashboard` on successful login; otherwise calls `user_error`.

>Tables: `users`  
>Depends on: `check_password_hash`, `get_db()`, `redirect`, `render_template`, `session`, `user_error`, `url_for`

### @logout()  

Logs the user out by clearing the session and redirects to the index route.

**Key Points:**  
1. Clears all session data.  
2. Redirects user to `index()`, which will then send them to `login()` if unauthenticated

>Tables: None  
>Depends on: `redirect`, `session`

### @register()  

Handles user registration: displays the registration form on GET requests and processes new user creation on POST requests.

**Key Points:**  
1. Validates all form fields.  
2. Checks if passwords match and email is not already registered.
3. Inserts new user into `users` table with `generate_password_hash`.
4. Flashes success message and redirects to `/login`.

>Tables: `users`  
>Depends on: `flash`, `get_db()`, `generate_password_hash`, `redirect`, `render_template`, `user_error`, `url_for`

### @dashboard()  

Displays the user’s dashboard. Currently under development. 

**Key Points:**  
1. Intended to show a summary of accounts, spending, and other metrics in the future.

>Tables: None  
>Depends on: `render_template`

[Return to TOC](#table-of-contents)

### @accounts()  

Displays the user’s account balances for Sprouting and Grounded accounts. Allows viewing balances by year and automatically ensures the current month is computed. 

This route fetches account balances from the `account_balances` table, splits accounts into Sprouting and Grounded classifications, organizes them by month, and computes totals for each month. 

**Key Points:**  
1. Determines the selected year from query parameters or defaults to the current year.
2. Automatically calls `archive_month()` to compute account totals and save monthly balances in data history.
3. Fetches and organizes Sprouting and Grounded accounts into dictionaries keyed by account ID.
4. Computes totals per month for both account classifications.

>Tables: `accounts`, `account_balances`, `account_types`  
>Depends on: `archive_month()`, `datetime`, `defaultdict`, `get_db()`,   `render_template`, `session`

### @edit_account()  

Allows users to manage their existing accounts: edit details, close, recover, or create new ones.

This route handles both open and closed accounts, updates monthly balances accordingly, and maintains historical accuracy via `archive_month()`.

**Key Points:**  
1. Supports updating account type, name, or balance for all open accounts.
2. Allows closing or recovering accounts without losing transaction history.
3. Automatically updates `account_balances` for the current month upon any edit.
4. Validates account types and balance formats before committing changes.
5. Adds new accounts with a unique name and type combination per user.
6. Uses `m_read()` for computing and `m_display()` for formatting balances.

>Tables: `accounts`, `account_balances`, `account_types`  
>Depends on: `archive_month()`, `datetime`, `defaultdict`, `flash`, `get_db()`, `m_display()`, `m_read`, `render_template`, `redirect`, `session`, `timedelta`, `url_for`

### @edit_atypes()  

Allows users to manage the creation, modification, and deletion of account types.

**Key Points:**  
1. Displays all user-specific account types with editable fields.
2. Prevents deletion of types currently used by any account.
3. Supports updates to name, abbreviation, and classification fields.
4. Adds new account types with validation to avoid duplicates.
5. Uses flash messages to communicate validation errors or success.

>Tables: `accounts`, `account_types`  
>Depends on: `flash`, `get_db()`, `render_template`, `redirect`, `session`, `url_for`

[Return to TOC](#table-of-contents)

### @edit_categories()  

Displays all user categories and subcategories, and allows the creation of new categories.

**Key Points:**  
1. Retrieves all user-specific categories and subcategories ordered by name.
2. Supports adding new categories with validation for duplication.
3. Redirects back to refresh the list after any change.

>Tables: `categories`, `subcategories`  
>Depends on: `flash`, `get_db()`, `render_template`, `redirect`, `session`, `url_for`

### @category_settings(cat_id)  

Manages a single category, identified by `cat_id`, and its associated subcategories.

**Key Points:**  
1. Accepts a cat_id parameter from the URL to identify the active category.
2. Loads the selected category and all its subcategories for editing.
3. Prevents duplicate category and subcategory names per user.
4. Prevents category deletion if there are existing subcategories in it.
5. Prevents subcategory deletion if linked to transactions. 
6. Supports moving subcategories between categories.
7. Automatically refreshes the page after any change for accurate state.

>Tables: `categories`, `subcategories`, `transactions`  
>Depends on: `flash`, `get_db()`, `render_template`, `redirect`, `session`, `url_for`

[Return to TOC](#table-of-contents)

### @transactions()

This route handles displaying, loading and deleting transactions.

It fetches categories, subcategories and open accounts - so only open accounts can be selected by the user when inputting new transactions; supports pagination of 30 items at a time; and recalculates account balances when a transaction is deleted.

**Key Points:**                
1. Loads transactions in steps of 30 (`offset` + `Load More`).
2. Joins `transactions`, `accounts`,`account_types` to create a `defaultdict` to be passed to the template.
3. Deletes transactions on POST and updates balances and monthly archives through `archive_month()`

>Tables: `accounts`, `account_types`, `categories`, `subcategories`, `transactions`  
>Depends on: `archive_month()`, `flash`, `get_db()`, `redirect`,  `render_template`, `session`, `url_for`

### @get_subcategories(category_id)

This route returns all subcategories from a category for the logged user.

It prompts the database for subcategories matching the `category_id` and `user_id`, orders them alphabetically, and converts them into a JSON format to be sent to the front-end.

*see transactions.html for further information*

**Key Points:**               
1. Lists subcategories alphabetically (`ASC`), for a given `category_id` from the `user_id` passed through the `session`.
2. Converts SQLite rows into dictionaries and returns them as JSON.

>Tables: `subcategories`   
>Depends on: `get_db()`, `jsonify`, `session`

### @new_transaction()

This route creates a new transaction without reloading the page.

It validates all fields, checks if the selected account is open, determines amount sign based on `flow` classification of transactions and account classification (`Grounded` or `Sprouting`), and updates monthly balances through `archive_month()`.

**Key Points:**                
1. Validates all inputs and ensures the account belongs to the user.
2. Uses `m_read()` to compute the amount value.
3. Adjusts transaction sign according to flow and account type.
4. Updates historical balances for the month and returns a JSON response.

>Tables: `accounts`, `account_types`, `transactions`  
>Depends on: `archive_month()`, `datetime`, `get_db()`, `jsonify`,  `m_read()`, `session`

### @edit_transaction(tr_id)

This route edits an existing transaction without reloading the page.

It compares the new values to the existing record, updates changed fields, and recalculates affected monthly archives / account balances for both the original and new transaction dates.

**Key Points:**                
1. Validates all inputs and ensures the transaction exists.
2. Recomputes signs for amounts based on flow and account type.
3. Commits only if any changes are detected.
4. Calls `archive_month()` for both new and old dates if the transaction date changes.

>Tables: `accounts`, `account_types`, `transactions`  
>Depends on: `archive_month()`, `datetime`, `get_db()`, `jsonify`,  `m_read()`, `session`

[Return to TOC](#table-of-contents)

---
## Folder: templates

### layout.html

This is the base layout that all pages extend. It defines the global structure of the web app: the header, navbar, footer, and Bootstrap integration. 

Key Points:  
1. Provides a consistent navigation bar across all pages.
2. Includes `get_flashed_messages()` logic for alert messages.
3. Defines two key blocks: `{% block title %}` for dynamic page titles ; `{% block main %}` for each page’s main content.
4. Integrates Bootstrap 5.3 and a custom stylesheet `(/static/styles.css)`.
5. Navbar automatically highlights the current active page based on `request.path`.
6. “Settings” dropdown links to all edit routes (`edit_categories`, `edit_account`, `edit_atypes`).

>Variables used: `get_flashed_messages()`, `request.path`  
>Filters Used: None  
>Depends on: All page templates

[Return to TOC](#table-of-contents)

## sub-folder: accounts
        
### accounts.html

Displays a yearly summary of all user accounts, separated into two classes: Sprouted (assets) and Grounded (liabilities). The decison to name them like that came from my plant theme. 

Allows selection of other years and provides link to add or edit accounts. 

**Key Points:**  
1. Fetches and display monthly balances from previous December and January through December of the current year. 

    *This design decision came from my habit of comparing account totals to previous months; whenever there is a change in year, I always find myself comparing how balances transitioned.* 

2. Totals for each month are shown at the bottom of each table.  
3. Two main tables: Sprouted (accounts for assets) and Grounded (accounts for liability)
4. Includes "+" button linking to `/edit_account` route for adding / editing accounts. 

>Extends: `layout.html`  
>Variables used: `grounded_acc`, `grounded_totals`, `sprouted_acc`, `sprouted_totals`, `year`, `years`   
>Filters Used: `money`   
>Depends on: `url_for('edit_account')`

### edit.html

Allows the user to add, edit, delete, and recover accounts.

The page is divided in two sections: one lists all open accounts in an editable table and provides, the second lists closed accounts that can be reactivated.

**Key Points:**

1. Displays all active accounts with editable form fields for type, name, and balance.
2. Provides a “Save Changes” button to update multiple accounts at once.
3. Includes a “Delete” option beside each account with a confirmation prompt to close it.
4. Offers an input row at the bottom of the table for adding a new account directly from the same page. (embedded on the same form)
5. Displays another table listing closed accounts, with a “Recover” button to reopen them if needed.
6. Includes a link to edit_atypes for adding or editing account types.

>Extends: `layout.html`  
>Variables used: `a_types_`, `accounts`, `c_accounts`   
>Filters Used: None   
>Depends on: `url_for('edit_account')`, `url_for('edit_atypes')`


[Return to TOC](#table-of-contents)


## sub-folder: authentication
            
### login.html

*The login and registration pages were intentionally kept minimal. I wanted them to feel calm and easy to use, aligned with the plant-growth theme of the app.* 

Handles user authentication and allows users to log into their account.

A “Register” link is included for new users who don’t yet have an account.

**Key Points:**  
1. Includes two main input fields: email and password, both required.
2. Uses the POST method to send data to the `/login` route for validation.
3. Includes a footer link guiding users to the registration page (`/register`) if they don’t yet have an account.

>Extends: `layout.html`  
>Variables used: None  
>Filters Used: None   
>Depends on: `url_for('login')`, `url_for('register')`
            
### register.html

Enables new users to create an account by submitting personal and login information.

**Key Points:**  
1. Contains fields for first name, last name, email, password, and confirm password, all marked as required.
2. Uses the POST method to send data to the `/register` route for validation.
3. Registration automatically redirects users to login upon successful signup.

>Extends: `layout.html`  
>Variables used: None   
>Filters Used: None   
>Depends on: `url_for('login')`, `url_for('register')`


[Return to TOC](#table-of-contents)

## sub-folder: reports
### monthly.html

Displays a monthly financial report for each subcategory of the selected year.

Allows the user to switch between years and view subcategory totals across all months.

**Key Points:**  
1. Uses a dropdown to select the year, submitting via GET to refresh data.
2. Generates a table with 13 columns (previous December + current year months).
3. Dynamically displays totals per subcategory, formatted using the custom money filter.

>Extends: `layout.html`  
>Variables used: `categories`, `subcat_totals`, `subcategories`, `year`, `years`  
>Filters Used: `money`   
>Depends on: `url_for('monthly')`

### yearly.html

Displays a yearly financial report for the amount of years a user has been registered.

**Key Points:**  
1. Generates a table with the number of columns equivalent to the number of years a user has been registered.
2. Dynamically displays totals per subcategory, formatted using the custom money filter.

>Extends: `layout.html`  
>Variables used: `categories`, `num_years`, `subcat_totals`, `subcategories`, `years`  
>Filters Used: `money`  
>Depends on: `url_for('yearly')`

[Return to TOC](#table-of-contents)

## sub-folder: settings
### set_atype.html

Manages account type definitions; allowing users to add, edit, or delete account types and assign each a classification (Sprouting or Grounded).

**Key Points:**  
1. Displays all existing account types with editable fields for type, abbreviation, and classification.
2. Includes a final row to add a new account type directly from the same table.
3. Provides a delete button beside each row with a confirmation prompt.
4. Explains the difference between Sprouting (assets you own) and Grounded (liabilities you owe) in a card below the table.

>Extends: `layout.html`  
>Variables used: `a_types`  
>Filters Used: None  
>Depends on: `url_for('edit_atypes')`

### set_categories.html

Displays all categories and their respective subcategories in a summarized, read-only layout.

*Instead of placing all category and subcategory editing tools on one page, I intentionally separated them to reduce confusion when managing nested data in the backend. It also avoids the need to scroll through a long, crowded form.*

Provides quick access to edit each category and the ability to create a new one.

**Key Points:**  
1. Lists all categories with their nested subcategories indented underneath.
2. Each category includes an Edit button that navigates to its detailed editing page.
3. Allows adding new categories directly from the bottom of the table.

>Extends: `layout.html`  
>Variables used: `categories`, `subcategories`  
>Filters Used: None  
>Depends on: `url_for('category_settings')`, `url_for('edit_categories')`

### set_categorysolo.html

Provides a focused view to edit a single category and its related subcategories.

Users can rename or delete the category, update subcategory names, move subcategories to another category, or create new subcategories.

**Key Points:**  
1. Editable category name at the top, with an option to delete it if no subcategories exist.
2. Each subcategory can be renamed, reassigned to another category, or deleted.
3. The bottom row allows the creation of a new subcategory directly under the same form.

>Extends: `layout.html`  
>Variables used: `categories`, `cat`, `subcategories`  
>Filters Used: None  
>Depends on: `url_for('category_settings')`, `url_for('edit_categories')`

[Return to TOC](#table-of-contents)

## sub-folder: transactions
### transactions.html

Displays all user transactions (both income and expenses) in an interactive table.

Users can view, add, edit, or delete transactions directly from this page using modal windows.

*The modals allowed me to handle the add / edit transaction actions separately in the backend and avoid full page reloads*

**Key Points:**  
1. Lists every transaction with fields for type, amount, category, subcategory, account, date, and action buttons (Edit / Delete).
2. Closed-account transactions appear grayed out and uneditable.
3. Includes a “Load More” button for pagination.
4. The "Add New" button opens the `#newTransactionModal`.
5. The "Edit" button opens the `#editTransactionModal` , which is prefilled with existing data from the database.
6. Subcategories on both modals are automatically populated upon selection of category. 
7. JavaScript reloads the full table upon modal sucessful form submission. 

>Extends: `layout.html`  
>Variables used: `accounts`, `categories`, `load_more`, `offset`, `subcategories`, `transactions`  
>Filters Used: `m_display`  
>Depends on: `url_for('transactions')`, `/subcategories/<category_id>`, `/transactions/new`, `/transactions/edit/<id>`

**Supporting Scripts**

<ins>Dynamic Subcategory fetching</ins> 

A JavaScript event listener monitors all `<select name="category">` elements.

When the user changes a category, a `fetch('/subcategories/<category_id>')` call retrieves the relevant subcategories and repopulates the dropdown list in real time.

<ins>Populate Edit Transaction Modal</ins>

When the user clicks an "Edit" button, JavaScript retrieves all data attributes from that transaction. These values are automatically filled into the `editTransactionForm`

If the associated account is closed, editing is blocked and the user receives an alert. 

<ins>Handle New Transaction Submission</ins>

The “Save New Transaction” button sends the newTransactionForm data via `fetch('/transactions/new')`.

The server responds with JSON indicating success or error. 

On success, the modal closes and the table reloads.

<ins>Handle Edit Transaction Submission</ins>

The “Save Edit Transaction” button sends the editTransactionForm data via `fetch('/transactions/edit/<tr_id>')`.

The form includes validation for missing IDs. The server responds with JSON indicating success or error. 

On success, the modal closes and the table reloads.

[Return to TOC](#table-of-contents)

### dashboard.html

This page is still under development. Eventually it will allow users to see a short summary of their current month's spending and maybe I will add a mascot here. 

Key Points:  
1. Placeholder text and comments are in place for future content.
2. Will extend `layout.html` once fully developed.

>Extends: `layout.html`  
>Variables used: None  
>Filters Used: None  
>Depends on: None

### error.html

Generic error page for displaying custom error codes and messages.

The app may still rely heavily on Flask’s default error handling unless explicitly wired to render this page. 

Key Points:  
1. Displays `code` and `message` passed from the backend.

>Extends: `layout.html`  
>Variables used: `code`, `message`  
>Filters Used: None  
>Depends on: `user_error(message, code)`

[Return to TOC](#table-of-contents)
    
---
## Folder: static

### sub-folder: brand

The brand folder is my default to items that I possibly would like to make customizable or may change my mind in the future. Colors, logos, images.

### styles.css

Obtained from Bootstrap and here I changed the default colors so my webpage would look more green
